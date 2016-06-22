#pragma once


template<class T>
class Singleton
{
	static T* _self;
	static int _refcount;
protected:
	Singleton()
	{
	}
	virtual ~Singleton()
	{
		_self = NULL;
	}
public:
	static T* getInstance();
	void FreeInstance();
};

template<class T>
T* Singleton<T>::_self = NULL;

template<class T>
int Singleton<T>::_refcount = 0;

template<class T>
T* Singleton<T>::getInstance()
{
	if (!_self)
		_self = new T;
	_refcount++;
	return _self;
};

/*возвращаем ссылку на ресурс, если все ссылки возвращены экземпляр объекта удаляется*/
template<class T>
void Singleton<T>::FreeInstance()
{
	if (--_refcount == 0)
	{
		delete this;
		_self = NULL;
	}
};

//template<class T>
//T* Singleton::_self = NULL;

