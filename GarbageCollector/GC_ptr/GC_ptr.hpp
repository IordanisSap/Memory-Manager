
namespace GC
{

    template <typename T>
    class ptr
    {
    public:
        ptr(T *ptr = nullptr) : m_ptr(ptr)
        {
            std::cout << "Creating pointer to address: " << m_ptr << std::endl;
        }
        ~ptr()
        {
            std::cout << "Deleting pointer to address: " << m_ptr << std::endl;
            delete m_ptr;
        }
        T *operator->() { return m_ptr; }
        T &operator*() { return *m_ptr; }
        ptr<T> &operator=(const ptr<T> &other) // Overloading assignment operator
        {
            if (this != &other) // Avoid self-assignment
            {
                std::cout << "Assigning pointer to address: " << other.m_ptr << std::endl;
            }
            return *this; // Return reference to the current object
        }

    private:
        T *m_ptr;
    };

} // namespace GC