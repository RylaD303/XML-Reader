#pragma once
#pragma once
template <typename T>
/**
	Classic Vector class that is a template for any type. it works with dynamic memory and is self-sufficient.
*/
class Vector
{
private:
	T* data;
	unsigned int size;
	unsigned int capacity;
	/**
		private Free method that deletes tre used dynamic memory.
	*/
	void Free()
	{
		delete[] this->data;
	}
public:
	/**
		Vector default constructor. Sets the capacity of the memory to 8.
	*/
	Vector()
	{
		this->data = new T[8];
		this->size = 0;
		this->capacity = 8;
	}
	/**
		Vector destructor, deletes the memory.
	*/
	~Vector()
	{
		this->Free();
	}
	/**
		Vector copy constructor.
	*/
	Vector(const Vector& other)
	{
		this->size = other.size;
		this->capacity = other.capacity;
		this->data = new T[this->capacity];
		for (unsigned int i = 0; i < this->size; i++)
		{
			this->data[i] = other.data[i];
		}
	}
	/**
		operator - =, in case the objects are different, it copies the other object into the current one and gets care of the dynamic memory.
	*/
	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			this->Free();
			this->size = other.size;
			this->capacity = other.capacity;
			this->data = new T[this->capacity];
			for (unsigned int i = 0; i < this->size; i++)
			{
				this->data[i] = other.data[i];
			}
		}
		return *this;
	}


	/**
		Normal getter, returns current size of the vector as value.
	*/
	unsigned int GetSize() const
	{
		return this->size;
	}


	/**
		Expand method. Doubles the capacity of the Vector and gets care of the dynamic memory.
		Copies the current objext into another one, deletes the current memory, creates new, double the capacity,
		and then copies the values back from the copy vector.
	*/
	void Expand()
	{
		Vector copy(*this);
		this->Free();
		this->capacity *= 2;
		this->data = new T[this->capacity];
		for (unsigned int i = 0; i <= size; i++)
		{
			this->data[i] = copy.data[i];
		}
	}
	/**
		Adds new value of the same type to the Vector and increases it's size. If the size gets too big, the vector expands.
	*/
	void Add(const T& something)
	{
		if (this->size + 1 > this->capacity)
		{
			this->Expand();
		}
		this->data[this->size] = something;
		this->size++;
	}

	/**
		Removes some object from the vector, checks if it has that object, otherwise does nothing.
	*/
	void Remove(const T& something)
	{
		bool found = false;
		unsigned int i = 0;
		for (i = 0; i < this->size; i++)
		{
			if (!found && this->data[i] == something)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			this->size--;
			for (i; i < this->size; i++)
			{
				this->data[i] = this->data[i + 1];
			}
		}
	}
	void Remove(unsigned int i)
	{
		if(i < this->size)
		{
			this->size--;
			for (i; i < this->size; i++)
			{
				this->data[i] = this->data[i + 1];
			}
		}
	}
	/**
		Sort Vector method.
	*/
	void Sort()
	{

	}//Not needed still

	/**
		Classic operator - [] const. Returns referense to the object from the vector with index i in the array. Only readable.
	*/
	T& operator[](const unsigned int i) const
	{
		return this->data[i];
	}
	/**
		Classic operator - []. Retrns referense to the object from the vector with index i in the array. The object is not const so it can be modified.
	*/
	T& operator[](const unsigned int i)
	{
		return this->data[i];
	}

};


