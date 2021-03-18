#pragma once
#include <map>
#include <iostream>

template<typename E, typename T>
class Box
{
protected :
	using m_Box = std::map<E, T>;
	m_Box My_Box;

public :
	Box() = default;
	virtual ~Box();
	virtual T Get_Box(E _find) = 0;
};

template<typename E, typename T>
inline Box<E, T>::~Box()
{

}