#include "Singleton.hpp"

template<typename T>
std::once_flag Singleton<T>::__once;

template<typename T>
std::shared_ptr<T> Singleton<T>::__instance = nullptr;
