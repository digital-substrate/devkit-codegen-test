// The public surface of a generated TypeScript package, one line per member:
//     module <TAB> export <TAB> member <TAB> kind <TAB> documented (0|1)
// A member reached through a static attribute (an attachment of a concept) is written
// `attribute.member`. The runtime the package carries (`_codegen/`) is counted where the
// package re-exports it, not as a module of its own.
//
//     node parity_surface.cjs <typescript-module-dir> <generated-dir>
const path = require("path");
const ts = require(process.argv[2]);

const root = path.resolve(process.argv[3]);
const src = path.join(root, "src");
const codegen = path.join(src, "_codegen") + path.sep;
const config = ts.getParsedCommandLineOfConfigFile(path.join(root, "tsconfig.json"), {}, {
  ...ts.sys,
  onUnRecoverableConfigFileDiagnostic: (d) => { throw new Error(ts.flattenDiagnosticMessageText(d.messageText, "\n")); },
});
const program = ts.createProgram(config.fileNames, config.options);
const checker = program.getTypeChecker();
const rows = [];

const documented = (symbol) =>
  ts.displayPartsToString(symbol.getDocumentationComment(checker)).trim() ? 1 : 0;

const inPackage = (node) => node.getSourceFile().fileName.startsWith(src);

const isPublic = (symbol) => {
  if (symbol.name.startsWith("_") || symbol.name.startsWith("__@")) return false;
  const declaration = symbol.valueDeclaration || (symbol.declarations || [])[0];
  if (!declaration) return true;
  const flags = ts.getCombinedModifierFlags(declaration);
  return !(flags & (ts.ModifierFlags.Private | ts.ModifierFlags.Protected))
    && !(declaration.name && declaration.name.kind === ts.SyntaxKind.PrivateIdentifier);
};

const ownedType = (type) => {
  const symbol = type.getSymbol() || type.aliasSymbol;
  return Boolean(symbol && (symbol.declarations || []).some(inPackage));
};

function members(module, name, prefix, type, kind, depth) {
  for (const property of checker.getPropertiesOfType(type)) {
    if (!isPublic(property) || (kind === "static" && property.name === "prototype")) continue;
    rows.push([module, name, prefix + property.name, kind, documented(property)]);
    const declaration = property.valueDeclaration;
    if (depth > 0 && declaration) {
      const held = checker.getTypeOfSymbolAtLocation(property, declaration);
      if (held.getCallSignatures().length === 0 && ownedType(held)) {
        members(module, name, `${prefix}${property.name}.`, held, "instance", depth - 1);
      }
    }
  }
}

for (const file of program.getSourceFiles()) {
  if (!file.fileName.startsWith(src) || file.fileName.startsWith(codegen)) continue;
  const module = path.relative(src, file.fileName).replace(/\.ts$/, "").split(path.sep).join("/");
  const moduleSymbol = checker.getSymbolAtLocation(file);
  if (!moduleSymbol) continue;

  for (const exported of checker.getExportsOfModule(moduleSymbol)) {
    const name = exported.name;
    if (name.startsWith("_")) continue;
    const symbol = exported.flags & ts.SymbolFlags.Alias ? checker.getAliasedSymbol(exported) : exported;
    const declaration = symbol.valueDeclaration || (symbol.declarations || [])[0];
    if (!declaration) continue;
    const home = declaration.getSourceFile();
    // Counted where it is declared; the runtime, where the package re-exports it.
    if (home !== file && !home.fileName.startsWith(codegen)) continue;

    const flags = symbol.flags;
    const kind = flags & ts.SymbolFlags.Class ? "class"
      : flags & ts.SymbolFlags.Function ? "function"
      : flags & ts.SymbolFlags.Variable ? "const"
      : flags & (ts.SymbolFlags.TypeAlias | ts.SymbolFlags.Interface) ? "type" : "other";
    rows.push([module, name, "", kind, documented(symbol)]);

    if (flags & ts.SymbolFlags.Class) {
      members(module, name, "", checker.getTypeOfSymbolAtLocation(symbol, declaration), "static", 1);
      members(module, name, "", checker.getDeclaredTypeOfSymbol(symbol), "instance", 0);
    } else if (flags & ts.SymbolFlags.Variable) {
      const type = checker.getTypeOfSymbolAtLocation(symbol, declaration);
      const constructors = type.getConstructSignatures();
      if (constructors.length) {
        // A container class, bound by a factory: `export const Vector_of_uint8 = vectorOf(...)`.
        members(module, name, "", type, "static", 1);
        members(module, name, "", constructors[0].getReturnType(), "instance", 0);
      } else if (ownedType(type)) {
        members(module, name, "", type, "static", 1);
      }
    }
  }
}

console.log(rows.map((row) => row.join("\t")).join("\n"));
