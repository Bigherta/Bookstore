#include <exception>
#include <regex>
#include <string>

template <class T>
class validator
{
   protected:
    T value;
    bool is_revert;

   public:
    validator(T val, bool revert_) : value(val), is_revert(revert_) {}
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
    validator &Not()
    {
        is_revert = !is_revert;
        return *this;
    }
    validator &And() { return *this; }
    validator &Or() { return *this; }
    validator &but() { return *this; }
};

template <class T>
class validator_str;

template <typename CharT>
class validator_str<std::basic_string<CharT>> : public validator<std::basic_string<CharT>>
{
   public:
    validator_str(std::basic_string<CharT> val, bool revert_) : validator<std::basic_string<CharT>>(val, revert_) {
    }
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

    validator_str &toBe(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::toBe(obj);
        return *this;
    }
    template <class U>
    validator_str &toBe()
    {
        validator<std::basic_string<CharT>>::template toBe<U>();
        return *this;
    }
    template <typename... Args>
    validator_str &toBeOneOf(const std::basic_string<CharT> &first, const Args &...rest)
    {
        validator<std::basic_string<CharT>>::toBeOneOf(first, rest...);
        return *this;
    }
    validator_str &le(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::le(obj);
        return *this;
    }
    validator_str &ge(std::basic_string<CharT> obj)
    {
        validator<std::basic_string<CharT>>::ge(obj);
        return *this;
    }
    validator_str &Not()
    {
        this->is_revert = !this->is_revert;
        return *this;
    }
    validator_str &And() { return *this; }
    validator_str &Or() { return *this; }
    validator_str &but() { return *this; }
};

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
