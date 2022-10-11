# WinRM 활성화 하기

> WinRM 관련 스크립트 정리

## 활성화 스크립트

`winrm`을 사용해 접속할 서버에서 아래 스크립트를 실행해주자.

```ps
winrm quickconfig --force

# https 활성화하기
winrm quickconfig --force -transport:https

# 일반 PC의 경우 네트워크 연결 형식을 `개인`으로 설정
Set-NetConnectionProfile -NetworkCategory Private

# IP 접속 제한 필터 세팅
Set-Item WSMan:\localhost\Service\IPv6Filter -value ""
Set-Item WSMan:\localhost\Service\IPv4Filter -value ""
```


## 활성화 여부 확인

### Listen 상태 확인

```ps
PS C:\windows\system32> winrm enumerate winrm/config/listener

Listener
    Address = *
    Transport = HTTP
    Port = 5985
    Hostname
    Enabled = true
    URLPrefix = wsman
    CertificateThumbprint
    ListeningOn = 127.0.0.1, 172.28.183.60, ::1, fe80::50f1:768d:2298:be33%6
```

### WinRM 서비스 설정 확인

```ps
PS C:\Windows\system32> winrm get winrm/config/service

Service
    RootSDDL = O:NSG:BAD:P(A;;GA;;;BA)(A;;GR;;;IU)S:P(AU;FA;GA;;;WD)(AU;SA;GXGW;;;WD)
    MaxConcurrentOperations = 4294967295
    MaxConcurrentOperationsPerUser = 1500
    EnumerationTimeoutms = 240000
    MaxConnections = 300
    MaxPacketRetrievalTimeSeconds = 120
    AllowUnencrypted = false
    Auth
        Basic = false
        Kerberos = true
        Negotiate = true
        Certificate = false
        CredSSP = false
        CbtHardeningLevel = Relaxed
    DefaultPorts
        HTTP = 5985
        HTTPS = 5986
    IPv4Filter = *
    IPv6Filter = *
    EnableCompatibilityHttpListener = false
    EnableCompatibilityHttpsListener = false
    CertificateThumbprint
    AllowRemoteAccess = true
```

### 방화벽 확인

```ps
PS C:\Windows\system32> Get-NetFirewallRule -Name 'WINRM*' | Select-Object Name

Name                            
----                            
WINRM-HTTP-In-TCP-NoScope       
WINRM-HTTP-In-TCP               
WINRM-HTTP-Compat-In-TCP-NoScope
WINRM-HTTP-Compat-In-TCP        
```

## 클라이언트 세팅

`winrm` 으로 요청을 보내가 위해서 대상 호스트를 클라이언트에서 등록해주어야 한다.

```ps
PS C:\Windows\system32> winrm set winrm/config/client '@{TrustedHosts="172.24.15.237"}'
Client
    NetworkDelayms = 5000
    URLPrefix = wsman
    AllowUnencrypted = false
    Auth
        Basic = true
        Digest = true
        Kerberos = true
        Negotiate = true
        Certificate = true
        CredSSP = false
    DefaultPorts
        HTTP = 5985
        HTTPS = 5986
    TrustedHosts = 172.24.15.237
```

### 연결 테스트

```ps
PS C:\Windows\system32> Test-WSMan -ComputerName 172.24.15.237 -Port 5985

wsmid           : http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd
ProtocolVersion : http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd
ProductVendor   : Microsoft Corporation
ProductVersion  : OS: 0.0.0 SP: 0.0 Stack: 3.0
```

소켓을 만들어서 하는 방법도 있다.
```ps
PS C:\Windows\system32> (New-Object System.Net.Sockets.TcpClient).ConnectAsync('172.24.15.237', 5985).Wait(500)
True
```

## 명령어 샘플

`PSCredential` 로 인증 객체를 만들어 요청을 보내주자

```ps
$username = ''
$password = ''
[SecureString]$securepassword = $password | ConvertTo-SecureString -AsPlainText -Force 
$credential = New-Object System.Management.Automation.PSCredential -ArgumentList $username, $securepassword

# 단일 명령어
Invoke-Command -ComputerName 172.24.15.237 -Credential $credential -ScriptBlock { ipconfig }

# 명령어 두 개 이상 보내기
Invoke-Command -ComputerName '172.24.15.237' -Port 5985 -Credential $credential -ScriptBlock {
    pwd
    ipconfig
}

# `;` 으로 구분자 줘서 한 줄로도 가능
Invoke-Command -ComputerName 172.24.15.237 -Credential $credential -ScriptBlock { pwd; ipconfig }
```


### 출력
```
Path                             PSComputerName
----                             --------------
C:\Users\Administrator\Documents 172.24.15.237 

Windows IP Configuration


Ethernet adapter 이더넷:

   Connection-specific DNS Suffix  . : mshome.net
   Link-local IPv6 Address . . . . . : fe80::50f1:768d:2298:be33%6
   IPv4 Address. . . . . . . . . . . : 172.24.15.237
   Subnet Mask . . . . . . . . . . . : 255.255.240.0
   Default Gateway . . . . . . . . . : 172.24.0.1
```