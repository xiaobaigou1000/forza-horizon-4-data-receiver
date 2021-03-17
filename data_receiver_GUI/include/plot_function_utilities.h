#include<Mahi/Gui.hpp>
#include<Mahi/Util.hpp>

template <typename T>
struct MemberFunctionTraits;

template <typename Return, typename Object>
struct MemberFunctionTraits<Return(Object::*)()>
{
    using ReturnType = Return;
    using ObjectType = Object;
};

template <typename Return, typename Object>
struct MemberFunctionTraits<Return(Object::*)() const>
{
    using ReturnType = Return;
    using ObjectType = Object;
};

template <auto convertX, auto convertY, typename DataType = MemberFunctionTraits<decltype(convertX)>::ObjectType>
auto MyGetterFunc(void* rawDataPointer, int idx)
{
    using XType = MemberFunctionTraits<decltype(convertX)>::ReturnType;
    using YType = MemberFunctionTraits<decltype(convertY)>::ReturnType;

    DataType* data = reinterpret_cast<DataType*>(rawDataPointer);
    XType x = ((data + idx)->*convertX)();
    YType y = ((data + idx)->*convertY)();
    return ImPlotPoint(static_cast<double>(x), static_cast<double>(y));
}
