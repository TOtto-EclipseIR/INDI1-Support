// file: ./src/libs/base/Singleton.h - Basic Singleton Design Pattern Implementation
#pragma once



class Singleton
{
protected:
    Singleton(void) {}
    ~Singleton() {}

public:
    static Singleton * instance(void)
    { if ( ! smpInstance) smpInstance = new Singleton(); return smpInstance; }

private:
    static Singleton * smpInstance;
};

Singleton* Singleton::smpInstance = nullptr;
