class Uncopyable
{
public:

protected:
    Uncopyable(){}
    ~Uncopyable(){}

private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator = (const Uncopyable&);
};
