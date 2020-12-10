//Programmer: Phillip LaFrance	//Student ID: 12398940
//Intructor: Patrick Taylor		//Section: A		//Date: 03/6/2018
//File: MyVector.hpp			//Description: "Recreates vector as a class"

/* Define all your MyVector-related functions here.
 * You do not need to include the h file.
 * It included this file at the bottom.
 */
/**
NOTES:
reserved_size = max size & storage size
data_size = current size
*/

template <typename T>
void swap(T &a, T &b)
{
    T tmp=a;
    a=b;
    b=tmp;
    return;
}

/**Default constructor*/
template <typename T>
MyVector<T>::MyVector()
{
    //cout << "MyVector created" << endl;
    m_data = new T[1];

    //tracks size of array
    //vector always has at least one spot in array for insertion
    reserved_size = 1;

    //tracks amount filled
    //(only valid indexes are between 0 and data_size-1; greater than would either be unfilled part of array or off end of array)
    //is valid for adding to array (if not at max), not valid for getting values (get at index=data_size should be invalid)
    //0 then array is empty, 0< then array has elements
    data_size = 0;
}

/**Destructor*/
// We're giving you this one for free
// and as a guide for the syntax.
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_data;
    m_data = NULL;
}

/**Operator =*/
//operator = (shallow copy)
//previous array delete??
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &source)
{
    //cout << "inside operator =" << endl;
    delete[] m_data;
    m_data = NULL;
    if(this != &source)
    {
        this->reserved_size = source.reserved_size;
        this->data_size = source.data_size;
        this->m_data = new T[reserved_size];
        for(int i=0; i < data_size; i++)
        {
            this->m_data[i] = source.m_data[i];
        }
    }
    return *this;
}

/**Copy constructor*/
//deep copy
template <typename T>
MyVector<T>::MyVector(const MyVector<T> &source)
{
    this->reserved_size = source.reserved_size;
    this->data_size = source.data_size;
    this->m_data = new T[reserved_size];

    for(int i=0; i < data_size; i++)
    {
        this->m_data[i] = source.m_data[i];
    }
}

/**Operator []*/
//operator []
template <typename T>
T & MyVector<T>::operator[](int i)
{
    if(i<0 || i>=data_size)
    {
        //cout << "ERROR: operator[] - index is invalid" << endl;
        throw OutOfBoundsException();
    }
    return m_data[i];
}

/**at*/
// Another example: remember, return type first,
// then scope just before the function name.
template <typename T>
T & MyVector<T>::at(int index)
{
    if(index<0 || index>=data_size)
        throw OutOfBoundsException();
    return m_data[index];
}

/**front*/
//
template <typename T>
T & MyVector<T>::front()
{
    if(data_size == 0)
        throw OutOfBoundsException();
    return m_data[begin()];
}

/**back*/
//
template <typename T>
T & MyVector<T>::back()
{
    if(data_size == 0)
        throw OutOfBoundsException();
    return m_data[end()];
}

/**capacity*/
//
template <typename T>
int MyVector<T>::capacity() { return reserved_size; }

/**reverse*/
//grow??
//double size on fill??  use with insert
template <typename T>
void MyVector<T>::reserve(int new_cap)
{
    if(new_cap > reserved_size)
    {
        T *tmp =  new T[new_cap];
        for(int i = begin(); i < end(); i++)
            tmp[i] = m_data[i];
        delete[] m_data;
        reserved_size = new_cap;
        m_data = tmp;
        return;
    }
    //cout << "new_cap must be greater than reserved_size" << endl;
    throw OutOfBoundsException();
}

/**shrink_to_fit*/
//called if reserved_size/4 > data_size
template <typename T>
void MyVector<T>::shrink_to_fit()
{
    //cout << "shrink_to_fit called" << endl;
    T *tmp;
    if(data_size>0)
    {
        tmp =  new T[data_size*2];
        for(int i = begin(); i < end(); i++)
            tmp[i] = m_data[i];
        reserved_size = data_size*2;
    }
    else
    {
        tmp = new T[1];
        reserved_size = 1;
    }
    delete[] m_data;
    m_data = tmp;
    return;
}

/**assign*/
//
template <typename T>
void MyVector<T>::assign(int cnt, const T &value)
{
    delete[] m_data;
    T *tmp =  new T[cnt];
    for(int i = begin(); i < cnt; i++)
        tmp[i] = value;
    reserved_size = cnt;
    data_size = cnt;
    m_data = tmp;
    return;
}

/**clear*/
//
template <typename T>
void MyVector<T>::clear()
{
    delete[] m_data; //other functions??
    reserved_size = 1;
    data_size = 0;
    m_data = NULL;
    return;
}

/**push_back*/
//only grow if already filled
template <typename T>
void MyVector<T>::push_back(const T &x)
{
    if(reserved_size == data_size) //checks if array is filled
    {
        reserve(reserved_size*2);
        m_data[data_size] = x;
        data_size++;
    }
    else
    {
        m_data[data_size] = x;
        data_size++;
    }
    return;
}

/**pop_back*/
//
template <typename T>
void MyVector<T>::pop_back()
{
    if(data_size <= 0)
        throw OutOfBoundsException();
    data_size--;
    if(reserved_size/4 > data_size)
        shrink_to_fit();
    return;
}

/**insert*/
//only grow if already filled
template <typename T>
void MyVector<T>::insert(int i, const T &x)
{
    if(i<0 || i>data_size) //can insert at end
        throw OutOfBoundsException();
    if(reserved_size == data_size) //checks if array is filled
        reserve(reserved_size*2);
    data_size++;
    for(int j = end(); j > i; j--)
        m_data[j] = m_data[j-1];
    m_data[i] = x;
    return;
}

/**remove*/
//
template <typename T>
void MyVector<T>::remove(int i)
{
    if(i<0 || i>data_size) //can remove at end
        throw OutOfBoundsException();
    for(int j = i; j < end(); j++) //last element is kept, but outside of range
        m_data[j] = m_data[j+1];
    data_size--;
    if(reserved_size/4 > data_size)
            shrink_to_fit();
    return;
}

/**size*/
//
template <typename T>
int MyVector<T>::size() { return data_size; }
