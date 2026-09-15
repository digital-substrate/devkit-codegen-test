#ifndef Viper_AttachmentMutating_hpp
#define Viper_AttachmentMutating_hpp
#include "Viper_AttachmentGetting.hpp"
#include "Viper_UUId.hpp"
#include "Viper_Values.hpp"
namespace Viper {
class Path;
class Value;
class AttachmentMutating : public AttachmentGetting {
public:
    virtual void set(std::shared_ptr<Attachment> const & attachment,
                     std::shared_ptr<ValueKey> const & key,
                     std::shared_ptr<Value const> const & value) = 0;
    virtual void diff(std::shared_ptr<Attachment> const & attachment,
                      std::shared_ptr<ValueKey> const & key,
                      std::shared_ptr<Value const> const & value,
                      bool recursive) = 0;
    virtual void update(std::shared_ptr<Attachment> const & attachment,
                        std::shared_ptr<ValueKey> const & key,
                        std::shared_ptr<Path const> const & path,
                        std::shared_ptr<Value const> const & value) = 0;

    // MODIFIER UN AGRÉGAT SANS L'ÉCRASER. `update` remplace ce qui est à l'adresse ; ces
    // huit-là ajoutent, retirent ou déplacent à l'intérieur. La distinction n'est pas un
    // confort : deux écritures concurrentes sur le même ensemble se fondent, alors que
    // deux remplacements s'écrasent.
    virtual void unionInSet(std::shared_ptr<Attachment> const & attachment,
                            std::shared_ptr<ValueKey> const & key,
                            std::shared_ptr<Path const> const & path,
                            std::shared_ptr<ValueSet const> const & value) = 0;

    virtual void subtractInSet(std::shared_ptr<Attachment> const & attachment,
                               std::shared_ptr<ValueKey> const & key,
                               std::shared_ptr<Path const> const & path,
                               std::shared_ptr<ValueSet const> const & value) = 0;

    virtual void unionInMap(std::shared_ptr<Attachment> const & attachment,
                            std::shared_ptr<ValueKey> const & key,
                            std::shared_ptr<Path const> const & path,
                            std::shared_ptr<ValueMap const> const & value) = 0;

    /// Retirer d'une map, c'est retirer des clés -- donc un ensemble, pas une map.
    virtual void subtractInMap(std::shared_ptr<Attachment> const & attachment,
                               std::shared_ptr<ValueKey> const & key,
                               std::shared_ptr<Path const> const & path,
                               std::shared_ptr<ValueSet const> const & value) = 0;

    virtual void updateInMap(std::shared_ptr<Attachment> const & attachment,
                             std::shared_ptr<ValueKey> const & key,
                             std::shared_ptr<Path const> const & path,
                             std::shared_ptr<ValueMap const> const & value) = 0;

    /// Un xarray a des positions stables : on insère avant l'une, on remplace à l'une, on
    /// retire l'une. Aucune des trois ne se dit avec un index.
    virtual void insertInXArray(std::shared_ptr<Attachment> const & attachment,
                                std::shared_ptr<ValueKey> const & key,
                                std::shared_ptr<Path const> const & path,
                                UUId const & beforePosition,
                                UUId const & newPosition,
                                std::shared_ptr<Value const> const & value) = 0;

    virtual void updateInXArray(std::shared_ptr<Attachment> const & attachment,
                                std::shared_ptr<ValueKey> const & key,
                                std::shared_ptr<Path const> const & path,
                                UUId const & position,
                                std::shared_ptr<Value const> const & value) = 0;

    virtual void removeInXArray(std::shared_ptr<Attachment> const & attachment,
                                std::shared_ptr<ValueKey> const & key,
                                std::shared_ptr<Path const> const & path,
                                UUId const & position) = 0;
};
}
#endif
