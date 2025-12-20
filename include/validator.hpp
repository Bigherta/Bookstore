#pragma once
#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP
#include <exception>
#include <regex>
#include <string>

/**
 * @class validator
 * @brief 用于验证值的模板类，支持链式调用。
 * @tparam T 要验证的值的类型。
 */
template <class T>
class validator
{
   protected:
    T value;
    bool is_revert;

   public:
    /**
     * @brief 构造函数。
     * @param val 要验证的值。
     * @param revert_ 是否反转逻辑。
     */
    validator(T val, bool revert_) : value(val), is_revert(revert_) {}

    /**
     * @brief 检查值是否等于给定对象。
     * @param obj 要比较的对象。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator &toBe(T obj)
    {
        if (value == obj && is_revert == false)
        {
            return *this;
        }
        if (!(value == obj) && is_revert == true)
        {
            return *this;
        }

        throw std::exception();
    }

    /**
     * @brief 检查值是否为的实例。
     * @tparam U 要检查的类型。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    template <class U>
    validator &toBe()
    {
        static_assert(std::is_base_of_v<U, T>, "T must be derived from U");
        if constexpr ((std::is_same_v<T, U> && !is_revert) || (!std::is_same_v<T, U> && is_revert))
        {
            return *this;
        }

        throw std::exception();
    }

    /**
     * @brief 检查值是否为给定选项之一。
     * @tparam Args 参数的类型。
     * @param first 第一个选项。
     * @param rest 其余选项。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    template <typename... Args>
    validator &toBeOneOf(const T &first, const Args &...rest)
    {
        if (!((value == first) || ... || (value == rest)) && is_revert == false)
        {
            throw std::exception();
        }
        if (((value == first) || ... || (value == rest)) && is_revert == true)
        {
            throw std::exception();
        }

        return *this;
    }

    /**
     * @brief 检查值是否小于或等于给定对象。
     * @param obj 要比较的对象。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator &le(T obj)
    {
        if (value <= obj && is_revert == false)
        {
            return *this;
        }
        if (value > obj && is_revert == true)
        {
            return *this;
        }

        throw std::exception();
    }

    /**
     * @brief 检查值是否大于或等于给定对象。
     * @param obj 要比较的对象。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator &ge(T obj)
    {
        if (value >= obj && is_revert == false)
        {
            return *this;
        }
        if (value < obj && is_revert == true)
        {
            return *this;
        }

        throw std::exception();
    }

    /**
     * @brief 反转下一个条件。
     * @return 此验证器的引用，用于链式调用。
     */
    validator &Not()
    {
        is_revert = !is_revert;
        return *this;
    }

    /**
     * @brief 逻辑与（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator &And() { return *this; }

    /**
     * @brief 逻辑或（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator &Or() { return *this; }

    /**
     * @brief 转折连词（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator &but() { return *this; }
};

/**
 * @class validator_str
 * @brief validator 的字符串类型特化。
 * @tparam CharT 字符类型。
 */
template <class T>
class validator_str;

template <typename CharT>
class validator_str<std::basic_string<CharT>> : public validator<std::basic_string<CharT>>
{
   public:
    /**
     * @brief 构造函数。
     * @param val 要验证的字符串值。
     * @param revert_ 是否反转逻辑。
     */
    validator_str(std::basic_string<CharT> val, bool revert_) : validator<std::basic_string<CharT>>(val, revert_) {
    }

    /**
     * @brief 检查字符串是否仅由给定字符串中的字符组成。
     * @param obj 包含允许字符的字符串。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator_str &toBeConsistedOf(const std::basic_string<CharT> &obj)
    {
        if (this->is_revert == false)
        {
            for (CharT ch : this->value)
            {
                if (obj.find(ch) == std::basic_string<CharT>::npos)
                {
                    throw std::exception();
                }
            }
            return *this;
        }
        else
        {
            for (CharT ch : this->value)
            {
                if (obj.find(ch) == std::basic_string<CharT>::npos)
                {
                    return *this;
                }
            }
            throw std::exception();
        }
    }

    /**
     * @brief 检查字符串是否匹配给定的正则表达式。
     * @param obj 正则表达式模式。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator_str &toMatch(const std::basic_string<CharT> &obj)
    {
        if (this->is_revert == false)
        {
            std::basic_regex<CharT> re(obj);
            if (std::regex_match(this->value, re))
            {
                return *this;
            }
            throw std::exception();
        }
        else
        {
            std::basic_regex<CharT> re(obj);
            if (!std::regex_match(this->value, re))
            {
                return *this;
            }
            throw std::exception();
        }
    }

    /**
     * @brief 检查字符串是否等于给定字符串。
     * @param obj 要比较的字符串。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator_str &toBe(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::toBe(obj);
        return *this;
    }

    /**
     * @brief 检查字符串是否为指定类型。
     * @tparam U 要检查的类型。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    template <class U>
    validator_str &toBe()
    {
        validator<std::basic_string<CharT>>::template toBe<U>();
        return *this;
    }

    /**
     * @brief 检查字符串是否为给定选项之一。
     * @tparam Args 参数的类型。
     * @param first 第一个选项。
     * @param rest 其余选项。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    template <typename... Args>
    validator_str &toBeOneOf(const std::basic_string<CharT> &first, const Args &...rest)
    {
        validator<std::basic_string<CharT>>::toBeOneOf(first, rest...);
        return *this;
    }

    /**
     * @brief 检查字符串是否小于或等于给定字符串。
     * @param obj 要比较的字符串。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator_str &le(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::le(obj);
        return *this;
    }

    /**
     * @brief 检查字符串是否大于或等于给定字符串。
     * @param obj 要比较的字符串。
     * @return 此验证器的引用，用于链式调用。
     * @throw std::exception 如果条件不满足。
     */
    validator_str &ge(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::ge(obj);
        return *this;
    }

    /**
     * @brief 反转下一个条件。
     * @return 此验证器的引用，用于链式调用。
     */
    validator_str &Not()
    {
        this->is_revert = !this->is_revert;
        return *this;
    }

    /**
     * @brief 逻辑与（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator_str &And() { return *this; }

    /**
     * @brief 逻辑或（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator_str &Or() { return *this; }

    /**
     * @brief 延续词（用于链式调用的占位符）。
     * @return 此验证器的引用，用于链式调用。
     */
    validator_str &but() { return *this; }
};

/**
 * @brief 为给定值创建验证器。
 * @tparam T 值的类型。
 * @param value 要验证的值。
 * @return 验证器对象。
 */
template <class T>
auto expect(T &&value)
{
    using DecayT = std::decay_t<T>;
    if constexpr (std::is_same_v<DecayT, std::string> || std::is_same_v<DecayT, std::wstring> ||
                  std::is_same_v<DecayT, std::u16string> || std::is_same_v<DecayT, std::u32string>)
    {
        return validator_str<DecayT>(std::forward<T>(value), false);
    }
    else
    {
        return validator<DecayT>(std::forward<T>(value), false);
    }
}
#endif