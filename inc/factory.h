#ifndef _FACTORY_H_
#define _FACTORY_H_

// Templated Factory class with variadic template support
template <typename BaseClass>
class Factory {

    struct BuilderBase
    {

    };

    template<typename... Args>
    struct Builder : BuilderBase
    {
        virtual void* build(Args...) = 0;
    };

    template<typename T, typename... Args>
    struct ConcreteBuilder : public Builder<Args...>, public std::enable_shared_from_this <ConcreteBuilder<T, Args...> >
    {
        virtual void* build(Args... args)
        {
            auto object = new T (std::forward<decltype(args)>(args)...);
            static std::vector< std::shared_ptr<T>> storage;
            std::shared_ptr<T> ptr;
            ptr.reset(object);
            storage.emplace_back(ptr);
            return static_cast<void*>(object);
        };

    };


public:
    static Factory& getInstance() {
        static Factory instance;
        return instance;
    }

    // Register a class with a specific name
    template <typename DerivedClass, typename ... Args>
    void registerClass(const std::string& name) 
    {
        static std::vector< std::shared_ptr<ConcreteBuilder<DerivedClass, Args...>>> storage;
        auto creator = new ConcreteBuilder<DerivedClass, Args...> ();
        std::shared_ptr<ConcreteBuilder<DerivedClass, Args...>> ptr;
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
            return  static_cast<BaseClass*> (( static_cast<Builder<Args...>* >(it->second) )->build(args...));
        }
        return nullptr;
    }

private:
    // Store each creator as an `std::any` to allow variadic lambdas
    std::map<std::string, BuilderBase* > creators;

    // Private constructor for singleton pattern
    Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;
};

#endif
