/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2017 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_BASEOPTIONPROPERTY_H
#define IVW_BASEOPTIONPROPERTY_H

#include <inviwo/core/properties/stringproperty.h>
#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/util/introspection.h>
#include <type_traits>
#include <iterator>

namespace inviwo {

/** 
 *  Base class for the option properties
 *  @see TemplateOptionProperty
 */
class IVW_CORE_API BaseOptionProperty : public Property {
public:
    BaseOptionProperty(std::string identifier, std::string displayName,
                       InvalidationLevel invalidationLevel = InvalidationLevel::InvalidOutput,
                       PropertySemantics semantics = PropertySemantics::Default);

    BaseOptionProperty(const BaseOptionProperty& rhs) = default;
    BaseOptionProperty& operator=(const BaseOptionProperty&) = default;

    virtual ~BaseOptionProperty() = default;

    virtual std::string getClassIdentifier() const override = 0;

    virtual void clearOptions() = 0;

    virtual size_t size() const = 0;
    virtual size_t getSelectedIndex() const = 0;
    virtual std::string getSelectedIdentifier() const = 0;
    virtual std::string getSelectedDisplayName() const = 0;
    virtual std::vector<std::string> getIdentifiers() const = 0;
    virtual std::vector<std::string> getDisplayNames() const = 0;

    virtual bool setSelectedIndex(size_t index) = 0;
    virtual bool setSelectedIdentifier(std::string identifier) = 0;
    virtual bool setSelectedDisplayName(std::string name) = 0;

    virtual bool isSelectedIndex(size_t index) const = 0;
    virtual bool isSelectedIdentifier(std::string identifier) const = 0;
    virtual bool isSelectedDisplayName(std::string name) const = 0;

    virtual void set(const Property* srcProperty) override;
};

template <typename T>
class OptionPropertyOption : public Serializable {
public:
    OptionPropertyOption() = default;
    OptionPropertyOption(const std::string& id, const std::string& name, T value)
        : id_(id), name_(name), value_(value) {}
    template <typename U = T,
              class = typename std::enable_if<std::is_same<U, std::string>::value, void>::type>
    OptionPropertyOption(const std::string& id, const std::string& name)
        : id_(id), name_(name), value_(id) {}

    template <typename U = T,
        class = typename std::enable_if<util::is_stream_insertable<U>::value, void>::type>
        OptionPropertyOption(const T& val)
        : id_(toString(val)), name_(camelCaseToHeader(toString(val))), value_(val) {}

    std::string id_;
    std::string name_;
    T value_;

    virtual void serialize(Serializer& s) const {
        s.serialize("id", id_);
        s.serialize("name", name_);
        s.serialize("value", value_);
    }
    virtual void deserialize(Deserializer& d) {
        d.deserialize("id", id_);
        d.deserialize("name", name_);
        d.deserialize("value", value_);
    }

    bool operator==(const OptionPropertyOption<T>& rhs) const {
        return id_ == rhs.id_ && name_ == rhs.name_ && value_ == rhs.value_;
    }
    bool operator!=(const OptionPropertyOption<T>& rhs) const { return !operator==(rhs); }
};

template <typename T>
class TemplateOptionProperty : public BaseOptionProperty {

private:
    template <typename U>
    struct MatchId {
        MatchId(const std::string& s) : s_(s) {}
        bool operator()(const OptionPropertyOption<U>& obj) const { return obj.id_ == s_; }

    private:
        const std::string& s_;
    };
    template <typename U>
    struct MatchName {
        MatchName(const std::string& s) : s_(s) {}
        bool operator()(const OptionPropertyOption<U>& obj) const { return obj.name_ == s_; }

    private:
        const std::string& s_;
    };
    template <typename U>
    struct MatchValue {
        MatchValue(const T& s) : s_(s) {}
        bool operator()(const OptionPropertyOption<U>& obj) const { return obj.value_ == s_; }

    private:
        const U& s_;
    };

public:
    InviwoPropertyInfo();
    typedef T valueType;

    TemplateOptionProperty(std::string identifier, std::string displayName,
                           InvalidationLevel invalidationLevel = InvalidationLevel::InvalidOutput,
                           PropertySemantics semantics = PropertySemantics::Default);

    TemplateOptionProperty(std::string identifier, std::string displayName,
                           const std::vector<OptionPropertyOption<T>>& options,
                           size_t selectedIndex = 0,
                           InvalidationLevel invalidationLevel = InvalidationLevel::InvalidOutput,
                           PropertySemantics semantics = PropertySemantics::Default);

    template <typename U = T,
              class = typename std::enable_if<util::is_stream_insertable<U>::value, void>::type>
    TemplateOptionProperty(std::string identifier, std::string displayName,
                           const std::vector<T>& options, size_t selectedIndex = 0,
                           InvalidationLevel invalidationLevel = InvalidationLevel::InvalidOutput,
                           PropertySemantics semantics = PropertySemantics::Default);

    TemplateOptionProperty(const TemplateOptionProperty<T>& rhs) = default;
    TemplateOptionProperty<T>& operator=(const TemplateOptionProperty<T>& that) = default;
    virtual TemplateOptionProperty<T>* clone() const override;
    virtual ~TemplateOptionProperty() = default;

    /**
     * \brief Adds an option to the property
     *
     * Adds a option to the property and stores it as a struct in the options_
     * The option name is the name of the option that will be displayed in the widget.
     */
    void addOption(std::string identifier, std::string displayName, T value);
    template <typename U = T,
              class = typename std::enable_if<std::is_same<U, std::string>::value, void>::type>
    void addOption(std::string identifier, std::string displayName) {
        addOption(identifier, displayName, identifier);
    }

    virtual void removeOption(size_t index);
    virtual void clearOptions() override;

    virtual size_t size() const override;
    virtual size_t getSelectedIndex() const override;
    virtual std::string getSelectedIdentifier() const override;
    virtual std::string getSelectedDisplayName() const override;
    T getSelectedValue() const;
    virtual std::vector<std::string> getIdentifiers() const override;
    virtual std::vector<std::string> getDisplayNames() const override;
    std::vector<T> getValues() const;

    virtual bool setSelectedIndex(size_t index) override;
    virtual bool setSelectedIdentifier(std::string identifier) override;
    virtual bool setSelectedDisplayName(std::string name) override;
    bool setSelectedValue(T val);
    virtual void replaceOptions(std::vector<std::string> ids, std::vector<std::string> displayNames,
                                std::vector<T> values);
    virtual void replaceOptions(std::vector<OptionPropertyOption<T>> options);

    virtual bool isSelectedIndex(size_t index) const override;
    virtual bool isSelectedIdentifier(std::string identifier) const override;
    virtual bool isSelectedDisplayName(std::string name) const override;
    bool isSelectedValue(T val) const;

    T get() const;
    void set(const T& value);
    virtual void set(const Property* srcProperty) override;

    /**
     * Sets the default state, since the constructor can't add any default state, you must call this
     * function after adding all the default options, usually in the processor constructor.
     * @see Property::setCurrentStateAsDefault()
     */
    virtual void setCurrentStateAsDefault() override;
    virtual void resetToDefaultState() override;

    virtual std::string getClassIdentifierForWidget() const override;
    virtual void serialize(Serializer& s) const override;
    virtual void deserialize(Deserializer& d) override;

    virtual Document getDescription() const override;

protected:
    size_t selectedIndex_;
    std::vector<OptionPropertyOption<T>> options_;

private:
    size_t defaultSelectedIndex_;
    std::vector<OptionPropertyOption<T>> defaultOptions_;
};


namespace detail {
template <typename T, typename std::enable_if<!std::is_enum<T>::value, int>::type = 0>
std::string getOptionPropertyClassIdentifier() {
    return "org.inviwo.OptionProperty" + Defaultvalues<T>::getName();
}
template <typename T, typename std::enable_if<std::is_enum<T>::value, int>::type = 0>
std::string getOptionPropertyClassIdentifier() {
    using ET = typename std::underlying_type<T>::type;
    return "org.inviwo.OptionPropertyEnum" + Defaultvalues<ET>::getName();
}

template <typename T, typename std::enable_if<!std::is_enum<T>::value, int>::type = 0>
std::string getClassIdentifierForWidget() {
    return getOptionPropertyClassIdentifier<T>();
}
template <typename T, typename std::enable_if<std::is_enum<T>::value, int>::type = 0>
std::string getClassIdentifierForWidget() {
    using ET = typename std::underlying_type<T>::type;
    return getOptionPropertyClassIdentifier<ET>();
}
}

template <typename T>
PropertyClassIdentifier(TemplateOptionProperty<T>, detail::getOptionPropertyClassIdentifier<T>());

template <typename T>
std::string TemplateOptionProperty<T>::getClassIdentifierForWidget() const {
    return detail::getClassIdentifierForWidget<T>();
}


using OptionPropertyUInt = TemplateOptionProperty<unsigned int>;
using OptionPropertyInt = TemplateOptionProperty<int>;
using OptionPropertySize_t = TemplateOptionProperty<size_t>;
using OptionPropertyFloat = TemplateOptionProperty<float>;
using OptionPropertyDouble = TemplateOptionProperty<double>;
using OptionPropertyString = TemplateOptionProperty<std::string>;

using OptionPropertyUIntOption = OptionPropertyOption<unsigned int>;
using OptionPropertyIntOption = OptionPropertyOption<int>;
using OptionPropertySize_tOption = OptionPropertyOption<size_t>;
using OptionPropertyFloatOption = OptionPropertyOption<float>;
using OptionPropertyDoubleOption = OptionPropertyOption<double>;
using OptionPropertyStringOption = OptionPropertyOption<std::string>;

template <typename T>
TemplateOptionProperty<T>::TemplateOptionProperty(std::string identifier, std::string displayName,
                                                  InvalidationLevel invalidationLevel,
                                                  PropertySemantics semantics)
    : BaseOptionProperty(identifier, displayName, invalidationLevel, semantics)
    , selectedIndex_(0)
    , defaultSelectedIndex_(0) {}

template <typename T>
TemplateOptionProperty<T>::TemplateOptionProperty(
    std::string identifier, std::string displayName,
    const std::vector<OptionPropertyOption<T>>& options, size_t selectedIndex,
    InvalidationLevel invalidationLevel, PropertySemantics semantics)
    : BaseOptionProperty(identifier, displayName, invalidationLevel, semantics)
    , selectedIndex_(std::min(selectedIndex, options.size() - 1))
    , options_(options)
    , defaultSelectedIndex_(selectedIndex_)
    , defaultOptions_(options_) {}

template <typename T>
template <typename U, class>
TemplateOptionProperty<T>::TemplateOptionProperty(std::string identifier, std::string displayName,
                                                  const std::vector<T>& options,
                                                  size_t selectedIndex,
                                                  InvalidationLevel invalidationLevel,
                                                  PropertySemantics semantics)
    : BaseOptionProperty(identifier, displayName, invalidationLevel, semantics)
    , selectedIndex_(std::min(selectedIndex, options.size() - 1))
    , options_()
    , defaultSelectedIndex_(selectedIndex_)
    , defaultOptions_() {

    for (const auto& option : options) {
        options_.emplace_back(option);
        defaultOptions_.emplace_back(option);
    }
}

template <typename T>
void TemplateOptionProperty<T>::addOption(std::string identifier, std::string displayName,
                                          T value) {
    options_.push_back(OptionPropertyOption<T>(identifier, displayName, value));

    // in case we add the first option, we also select it
    if (options_.size() == 1) {
        selectedIndex_ = 0;
    }

    propertyModified();
}

template <typename T>
void TemplateOptionProperty<T>::removeOption(size_t index) {
    std::string id = getSelectedIdentifier();
    options_.erase(options_.begin() + index);
    if (!setSelectedIdentifier(id)) {
        selectedIndex_ = 0;
    }
    propertyModified();
}

template <typename T>
void TemplateOptionProperty<T>::clearOptions() {
    options_.clear();
    selectedIndex_ = 0;
}

// Getters
template <typename T>
size_t TemplateOptionProperty<T>::size() const {
    return options_.size();
}

template <typename T>
size_t TemplateOptionProperty<T>::getSelectedIndex() const {
    return selectedIndex_;
}

template <typename T>
std::string TemplateOptionProperty<T>::getSelectedIdentifier() const {
    return options_[selectedIndex_].id_;
}

template <typename T>
std::string TemplateOptionProperty<T>::getSelectedDisplayName() const {
    return options_[selectedIndex_].name_;
}

template <typename T>
T TemplateOptionProperty<T>::getSelectedValue() const {
    return options_[selectedIndex_].value_;
}

template <typename T>
std::vector<std::string> TemplateOptionProperty<T>::getIdentifiers() const {
    std::vector<std::string> result;
    for (size_t i = 0; i < options_.size(); i++) {
        result.push_back(options_[i].id_);
    }
    return result;
}

template <typename T>
std::vector<std::string> TemplateOptionProperty<T>::getDisplayNames() const {
    std::vector<std::string> result;
    for (size_t i = 0; i < options_.size(); i++) {
        result.push_back(options_[i].name_);
    }
    return result;
}

template <typename T>
std::vector<T> TemplateOptionProperty<T>::getValues() const {
    std::vector<T> result;
    for (size_t i = 0; i < options_.size(); i++) {
        result.push_back(options_[i].value_);
    }
    return result;
}

// Setters
template <typename T>
bool TemplateOptionProperty<T>::setSelectedIndex(size_t option) {
    if (selectedIndex_ == option) {
        return true;
    } else if (option < options_.size()) {
        selectedIndex_ = option;
        propertyModified();
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool TemplateOptionProperty<T>::setSelectedIdentifier(std::string identifier) {
    auto it = util::find_if(options_, MatchId<T>(identifier));
    if (it != options_.end()) {
        size_t dist = std::distance(options_.begin(), it);
        if (selectedIndex_ != dist) {
            selectedIndex_ = dist;
            propertyModified();
        }
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool TemplateOptionProperty<T>::setSelectedDisplayName(std::string name) {
    auto it = util::find_if(options_, MatchName<T>(name));
    if (it != options_.end()) {
        size_t dist = std::distance(options_.begin(), it);
        if (selectedIndex_ != dist) {
            selectedIndex_ = dist;
            propertyModified();
        }
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool TemplateOptionProperty<T>::setSelectedValue(T val) {
    auto it = util::find_if(options_, MatchValue<T>(val));
    if (it != options_.end()) {
        size_t dist = std::distance(options_.begin(), it);
        if (selectedIndex_ != dist) {
            selectedIndex_ = dist;
            propertyModified();
        }
        return true;
    } else {
        return false;
    }
}

template <typename T>
void TemplateOptionProperty<T>::replaceOptions(std::vector<std::string> ids,
                                                           std::vector<std::string> displayNames,
                                                           std::vector<T> values) {
    std::string selectId{};
    if (!options_.empty()) selectId = getSelectedIdentifier();

    options_.clear();
    for (size_t i = 0; i < ids.size(); i++)
        options_.emplace_back(ids[i], displayNames[i], values[i]);

    auto it = util::find_if(options_, MatchId<T>(selectId));
    if (it != options_.end()) {
        selectedIndex_ = std::distance(options_.begin(), it);
    } else {
        selectedIndex_ = 0;
    }
    propertyModified();
}

template <typename T>
void TemplateOptionProperty<T>::replaceOptions(
    std::vector<OptionPropertyOption<T>> options) {
    std::string selectId{};
    if (!options_.empty()) selectId = getSelectedIdentifier();

    options_ = std::move(options);
    auto it = util::find_if(options_, MatchId<T>(selectId));
    if (it != options_.end()) {
        selectedIndex_ = std::distance(options_.begin(), it);
    } else {
        selectedIndex_ = 0;
    }
    propertyModified();
}

// Is...
template <typename T>
bool TemplateOptionProperty<T>::isSelectedIndex(size_t index) const {
    return index == selectedIndex_;
}

template <typename T>
bool TemplateOptionProperty<T>::isSelectedIdentifier(std::string identifier) const {
    return identifier == options_[selectedIndex_].id_;
}

template <typename T>
bool TemplateOptionProperty<T>::isSelectedDisplayName(std::string name) const {
    return name == options_[selectedIndex_].name_;
}

template <typename T>
bool TemplateOptionProperty<T>::isSelectedValue(T val) const {
    return val == options_[selectedIndex_].value_;
}

// Convenience
template <typename T>
T TemplateOptionProperty<T>::get() const {
    return options_[selectedIndex_].value_;
}

template <typename T>
void TemplateOptionProperty<T>::set(const T& value) {
    setSelectedValue(value);
}

template <typename T>
void TemplateOptionProperty<T>::set(const Property* srcProperty) {
    BaseOptionProperty::set(srcProperty);
}

template <typename T>
void TemplateOptionProperty<T>::resetToDefaultState() {
    options_ = defaultOptions_;
    selectedIndex_ = defaultSelectedIndex_;

    if (defaultOptions_.empty()) {
        LogWarn("Resetting option property: " + this->getIdentifier() +
                " to an empty option list. Probably the default values have never been set, " +
                "Remember to call setCurrentStateAsDefault() after adding all the options.")
    }

    Property::resetToDefaultState();
}

template <typename T>
void TemplateOptionProperty<T>::setCurrentStateAsDefault() {
    Property::setCurrentStateAsDefault();
    defaultSelectedIndex_ = selectedIndex_;
    defaultOptions_ = options_;
}

template <typename T>
void TemplateOptionProperty<T>::serialize(Serializer& s) const {
    BaseOptionProperty::serialize(s);
    if (this->serializationMode_ == PropertySerializationMode::None) return;

    if ((this->serializationMode_ == PropertySerializationMode::All ||
         options_ != defaultOptions_) &&
        options_.size() > 0) {
        s.serialize("options", options_, "option");
    }
    if ((this->serializationMode_ == PropertySerializationMode::All ||
         selectedIndex_ != defaultSelectedIndex_) &&
        options_.size() > 0) {
        s.serialize("selectedIdentifier", getSelectedIdentifier());
    }
}

template <typename T>
void TemplateOptionProperty<T>::deserialize(Deserializer& d) {
    BaseOptionProperty::deserialize(d);
    if (this->serializationMode_ == PropertySerializationMode::None) return;

    auto oldIndex = selectedIndex_;
    auto oldOptions = options_;

    // We need to reset to default since that state was never serialized.
    if (this->serializationMode_ != PropertySerializationMode::All) {
        options_ = defaultOptions_;
        selectedIndex_ = defaultSelectedIndex_;
    }

    d.deserialize("options", options_, "option");

    if (!options_.empty()) {
        std::string identifier;
        d.deserialize("selectedIdentifier", identifier);
        auto it = util::find_if(options_, MatchId<T>(identifier));
        if (it != options_.end()) {
            selectedIndex_ = std::distance(options_.begin(), it);
        }
    } else {
        selectedIndex_ = 0;
    }
    
    if (oldIndex != selectedIndex_ || oldOptions != options_) propertyModified();
}

template <typename T>
Document TemplateOptionProperty<T>::getDescription() const {
    using P = Document::PathComponent;
    using H = utildoc::TableBuilder::Header;

    Document doc = BaseOptionProperty::getDescription();

    if (options_.size() > 0) {
        auto table = doc.get({ P("html"), P("body"), P("table", {{"identifier", "propertyInfo"}}) });
        utildoc::TableBuilder tb(table);
        tb(H("Selected Index"), selectedIndex_);
        tb(H("Selected Name"), options_[selectedIndex_].name_);
        tb(H("Selected Value"), options_[selectedIndex_].value_);
    }
    return doc;
}

template <typename T>
TemplateOptionProperty<T>* TemplateOptionProperty<T>::clone() const {
    return new TemplateOptionProperty<T>(*this);
}

}  // namespace inviwo

#endif  // IVW_BASEOPTIONPROPERTY_H
