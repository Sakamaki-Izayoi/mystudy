#pragma once
//#include "stdafx.h"
#include "util.h"
#include "snapshot_process.h"
#include "Process.h"
#include "Memory.h"
#include "inject.h"
#include "Services.h"

///git clone https://github.com/Microsoft/vcpkg.git
///pushd vcpkg
///.\bootstrap-vcpkg.bat
///.\vcpkg integrate install

//����
#define ASIO_STANDALONE
#include "asio.hpp"
#include "pkg_msg.h"
#include "client.h"
#include "server.h"

#include "lsp_helper.h"

//vcpkg install msgpack msgpack:x64-windows
#include <msgpack.hpp>
//https http
//vcpkg install cpr cpr:x64-windows
//��Ҫ��ͷ�ļ�copyһ��
//#include <cpr\cpr.h>
