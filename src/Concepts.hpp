
#ifndef CONCEPTS_HPP_INCLUDED
#define CONCEPTS_HPP_INCLUDED


#define IS_CALLABLE_MEMBER(F, Type) impl::Callable_##F<Type>::value

#include "Concepts.ipp"
/**
 *@namespace Concepts
 *@brief toto2
**/
namespace Concepts
{

/**
 *@class HasId
 *@brief Allows for static and dynamic testing of the Id Concept
 *@pre One of the two following conditions must be followed :
 *- C has none of the functions id, maxId, fromId
 *- C follows the IdConcept which is described @ref ConceptId "here".
 *@author Julien
**/
template<typename C>
struct HasId
{
    /**
     *@brief is true if C follows the Id concept (described @ref ConceptId "here").
     *@author Julien
     *@todo test for check and randomInstance
     *@todo hide the value of value in the documentation
    **/
    static constexpr bool value = impl::HasIdImpl<C, std::is_class<C>::value>::value;

    /**
     *@anchor ConceptId
     *@brief If HasId<C>::value = true, checks if C::id, C::maxId, C::fromId respect the dynamic part of the concept id concept. Otherwise does not do anything.
     *
     *@details Respecting the Id concept means :
     *- Having all the functions needed for all that follows
     *- From x = 0 to maxId -1 we have :
     *  -# fromId(x) never throws
     *  -# We have check(fromId(x))
     *  -# id(fromId(x)) never throws and is equal to x
     *- For each randomInstance :
     *  -# id(randomInstance) does not throw
     *  -# id(randomInstance) is between 0 and maxId-1
     *- For each x >= maxId, fromId throws
     *
     *@throw never throws
     *@note this function is equivalent to a test.
     *@author Julien
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct HasRandomInstance
{
    static constexpr bool value = impl::HasRandomInstanceImpl<C, std::is_class<C>::value>::value;
    /**
     *@anchor ConceptRandomInstance
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct IsCheckable
{

    static constexpr bool value=true;
    /**
     *@anchor ConceptCheck
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct IsEqualityComparable
{

    static constexpr bool value = true;
    /**
     *@anchor ConceptEquality
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct IsPrintable
{

    static constexpr bool value = true;
    /**
     *@anchor ConceptPrint
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct IsSerializable
{

    static constexpr bool value = true;
    /**
     *@anchor ConceptSerialize
    **/
    static void test(unsigned n = 1000);
};

template<typename C>
struct IsStringConstructible
{

    static constexpr bool value = true;
    /**
     *@anchor ConceptStringConstructible
    **/
    static void test(unsigned n = 1000);
};
}


#endif // CONCEPTS_HPP_INCLUDED

