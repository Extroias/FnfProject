#ifndef DELEGATE_H
#define DELEGATE_H

template <typename... Params>
class Delegate
{
protected:
  void *object = nullptr;
  virtual bool IsEqual (const Delegate<Params...> &other) const {return false;} 

public:
    virtual void operator()(Params...) = 0;
    virtual Delegate<Params...>* clone() const = 0;
  friend bool operator==(const Delegate<Params...> &del1, const Delegate<Params...> &del2)
  {
    return del1.object == del2.object && typeid(del1) == typeid(del2) && del1.IsEqual(del2);
  }
  void* getObject() { return object; }
  Delegate(){}
  
  template<typename... Args>
  class General;
  template<typename... Args>
  General(std::function<void(Params..., Args...)> func, Args... args) -> General<Args...>;
  template <class Object, typename... Args>
  class Member;
};

template<typename... Args>
using GeneralDelegate = Delegate<Args...>::template General;

template <typename... Params>
template <typename... Args>
class Delegate<Params...>::General : public Delegate<Params...>
{
  private:
  std::shared_ptr<std::function<void(Params..., Args...)>> func;
  std::tuple<Args...> args;
  bool IsEqual(const Delegate<Params...> &other) const override
  {
    const General &obj = static_cast<const General &>(other);
    return func == obj.func && args == obj.args;
  }

public:
  General(std::function<void(Params..., Args...)> func, Args... args) : args(args...)
  {
    this->func = std::make_shared<std::function<void(Params..., Args...)>>(func);
  }
  General(){}
  Delegate<Params...>* clone() const override
  {
    return new General<Args...>(*this);
  }
  void operator()(Params... params) override
  {
    std::apply(*func, std::tuple_cat(std::make_tuple(params...), args));
  }
};

template <typename... Params>
template <class Object, typename... Args>
class Delegate<Params...>::Member : public Delegate<Params...>
{
 private:
  void (Object::*fp)(Params..., Args...);
  std::tuple<Args...> args;
  bool IsEqual(const Delegate<Params...> &other) const override
  {
    const Member &obj = static_cast<const Member &>(other);
    return fp == obj.fp && args == obj.args;
  }
   
public:
  void operator()(Params... params) override
  {
    Object* obj = static_cast<Object*>(object);
    std::apply(fp,std::tuple_cat(std::make_tuple(obj),std::make_tuple(params...),args));
  }
  Member(void (Object::*fp)(Params..., Args...), Object* objectPtr, Args... args) : args(args...)
  {
     this->object = objectPtr;
     this->fp = fp;
  }
  Member(){}
  Delegate<Params...>* clone() const override
  {
    return new Member<Object,Args...>(*this);
  }
};

template<class Object,typename... Params, typename... Args,size_t... Is>
auto MakeDelegateUtil(void (Object::*fp)(Params...), Object* objectPtr, std::index_sequence<Is...>, Args... args)
{
  return typename Delegate<std::tuple_element_t<Is, std::tuple<Params...>>...>::template Member<Object, Args...>(fp, objectPtr, args...);
}
template<size_t N = 0,class Object, typename... Params, typename... Args>
auto MakeDelegate(void (Object::*fp)(Params...), Object* objectPtr, Args... args)
{
  return MakeDelegateUtil(fp, objectPtr, std::make_index_sequence<N>(), args...);
};
template<typename... Params, typename... Args,size_t... Is>
auto MakeDelegateUtil(std::function<void(Params...)> func, std::index_sequence<Is...>, Args... args)
{
  return typename Delegate<std::tuple_element_t<Is, std::tuple<Params...>>...>::template General<Args...>(func, args...);
};
template<size_t N = 0,typename... Params,typename... Args>
auto MakeDelegate(std::function<void(Params...)> func, Args... args)
{
  return MakeDelegateUtil(func, std::make_index_sequence<N>(), args...);
};

#endif // DELEGATE_H