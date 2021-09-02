#include <Windows.h>
#include <process.h>
#include <iostream>


struct Lock : public CRITICAL_SECTION
{
    Lock() {
        constexpr DWORD dwSpinCount = 4000;
        BOOL bRet = ::InitializeCriticalSectionAndSpinCount(this, dwSpinCount);
        if (!bRet) {
            std::cout << "bRet `InitializeCriticalSectionAndSpinCount` " << bRet << std::endl;
        }
    }

    virtual ~Lock() {
        ::DeleteCriticalSection(this);
    }

    void lock() {
        ::EnterCriticalSection(this);
    }

    void unLock() {
        ::LeaveCriticalSection(this);
    }
};

class LockHelper
{
public:
    LockHelper(Lock* pLock) : m_pLock(pLock) {
        pLock->lock();
    }

    virtual ~LockHelper() {
        m_pLock->unLock();
    }

    operator int() const {
        return 0;
    }

private:
    Lock* m_pLock;
};

Lock g_lock;

unsigned __stdcall veryBusyWorker(void*)
{
    std::cout << "call " << __FUNCTION__ << std::endl;

    if (LockHelper _lock = LockHelper(&g_lock)) {
        __assume(0);
    }
    else {
        std::cout << "enter " << __FUNCTION__ << std::endl;
        ::Sleep(1000 * 60 * 30);
    }

    std::cout << "leave " << __FUNCTION__ << std::endl;
    return 0;
}

unsigned __stdcall normalWorker(void*)
{
    std::cout << "call " << __FUNCTION__ << std::endl;

    if (LockHelper _lock = LockHelper(&g_lock)) {
        __assume(0);
    }
    else {
        std::cout << "enter " << __FUNCTION__ << std::endl;
        ::Sleep(1000 * 1);
    }

    std::cout << "leave " << __FUNCTION__ << std::endl;
    return 0;
}

int main()
{
    HANDLE hWaitBusy = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (!hWaitBusy) {
        std::cout << "exit failed to `CreateEvent` " << hWaitBusy << std::endl;
        return 1;
    }

    unsigned int tid = 0;
    HANDLE hBusy = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, veryBusyWorker, nullptr, CREATE_SUSPENDED, &tid));
    HANDLE hNormal = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, normalWorker, nullptr, CREATE_SUSPENDED, &tid));

    if (!hBusy || !hNormal) {
        std::cout << "exit failed to `_beginthreadex` " << hBusy << ", " << hNormal << std::endl;
        return 1;
    }

    ::ResumeThread(hBusy);
    ::ResumeThread(hNormal);

    ::WaitForSingleObject(hWaitBusy, INFINITE);
    std::cout << "exit" << std::endl;
}
