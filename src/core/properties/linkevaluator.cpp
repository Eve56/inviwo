
#include "inviwo/core/properties/linkevaluator.h"

namespace inviwo {

LinkEvaluator::LinkEvaluator() {}

void LinkEvaluator::evaluate(Property* src, Property *dst) {
    ivwAssert(src!=0, "source property expected");
    ivwAssert(dst!=0, "destination property expected");
    if (canLink(src, dst)) {
        dst->setVariant(src->getVariant());
    }
}

bool LinkEvaluator::canLink(Property* src, Property *dst) {     
    return canConvert(src->getVariant(), dst->getVariant());
}

bool LinkEvaluator::canConvert(Variant& src, Variant& dst) {
    if (src.getType() == Variant::VariantTypeInvalid || dst.getType() == Variant::VariantTypeInvalid) {
        //Error message
        return false;
    }    
    return Variant::canConvert(src.getType(), dst.getType());
}

}