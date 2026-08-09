#ifndef SK_H
#define SK_H

class Sk
{
public:
    Sk(const Sk& instance) = delete;
    Sk& operator=(const Sk&) = delete;
    
    static Sk& GetInstance();
    void Run(int argc, char **argv);
private:
    Sk();
    ~Sk();
};

#endif
