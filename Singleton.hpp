#pragma once

#include <memory>
#include <mutex>
#include <type_traits>
#if __cplusplus >= 202003L
template<class T>
concept has_default_contruct = requires(T t)
{
    { T{} } -> std::same_as<T>;
};

template<class T>
requires has_default_contruct<T>
#else
template<class T>
#endif
class Singleton final
{
public:
    static std::shared_ptr<T> instance()
    {
        std::call_once(__once, []()
            {
                __instance = std::make_shared<T>();
            });
        return __instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton() = default;
    static std::once_flag __once;
    static std::shared_ptr<T> __instance;
};
