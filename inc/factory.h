#ifndef _FACTORY_H_
#define _FACTORY_H_

namespace cogui
{

// Templated factory class with variadic template support
template <typename BaseClass>
class factory {

    struct builder_base
    {

    };

    template<typename... Args>
    struct builder : builder_base
    {
        virtual void* build(Args...) = 0;
    };

    template<typename T, typename... Args>
    struct concrete_builder : public builder<Args...>, public std::enable_shared_from_this <concrete_builder<T, Args...> >
    {
        virtual void* build(Args... args)
        {
            auto object = new T (std::forward<decltype(args)>(args)...);
            static std::vector< std::shared_ptr<T>> storage;
            std::shared_ptr<T> ptr;
            ptr.reset(object);
            storage.emplace_back(ptr);
            return static_cast<void*>(object);
        }

    };


public:
    static factory& instance()
    {
        static factory instance;
        return instance;
    }

    // Register a class with a specific name
    template <typename DerivedClass, typename ... Args>
    void register_class(const std::string& name)
    {
        static std::vector< std::shared_ptr<concrete_builder<DerivedClass, Args...>>> storage;
        auto creator = new concrete_builder<DerivedClass, Args...> ();
        std::shared_ptr<concrete_builder<DerivedClass, Args...>> ptr;
        ptr.reset(creator);
        storage.emplace_back(ptr);
        creators.emplace(name, creator );
    }

    // Create an object with a variable number of arguments
    template <typename... Args>
    BaseClass* create(const std::string& name, Args... args) const 
    {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return  static_cast<BaseClass*> (( static_cast<builder<Args...>* >(it->second) )->build(args...));
        }
        return nullptr;
    }

private:
    // Store each creator as an `std::any` to allow variadic lambdas
    std::map<std::string, builder_base* > creators;

    // Private constructor for singleton pattern
    factory() = default;
    factory(const factory&) = delete;
    factory& operator=(const factory&) = delete;
};

}

#endif
