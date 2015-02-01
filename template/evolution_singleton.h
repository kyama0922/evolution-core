#ifndef __EVOLUTION_TEMPLATE_SINGLETON_H_
#define __EVOLUTION_TEMPLATE_SINGLETON_H_

#include <evolution_type.h>

namespace EVOLUTION{
    namespace TEMPLATE{
        class IPublicObject{
        public:
            virtual ~IPublicObject(){}
        };

        //シングルトンテンプレート
        template <class _T>
        class SingletonManager : public IPublicObject{
        private:
            SingletonManager(const SingletonManager& t){}
        protected:
            virtual ~SingletonManager(){}
            SingletonManager(){
                static class _c {
                private:
                    IPublicObject* mp_object;
                public:
                    _c(IPublicObject* object) :mp_object(object){
                    }
                    ~_c(){
                        EVOLUTION_DELETE(mp_object);
                    }
                }_C(this);
            }
        public:
            //インスタンスの取得
            static _T* GetInstance(void)
            {
                static _T* myself = nullptr;
                return (myself) ? myself : myself = new _T();
            }
        };
    }
}
#endif //!__EVOLUTION_TEMPLATE_SINGLETON_H_