#include <stdio.h>
#include <windows.h>
#include <physicalmonitorenumerationapi.h>

#if !__MINGW32__
#include <lowlevelmonitorconfigurationapi.h>
#else
// header is missing from mingw-w64?
extern BOOL WINAPI SetVCPFeature(
  _In_  HANDLE hMonitor,
  _In_  BYTE bVCPCode,
  _In_  DWORD dwNewValue
);
#endif

BOOL CALLBACK monitor_enum(
  _In_ HMONITOR hMonitor,
  _In_ HDC      hdcMonitor,
  _In_ LPRECT   lprcMonitor,
  _In_ LPARAM   dwData
) {
	HMONITOR* monitor = (HMONITOR*)dwData;
	*monitor = hMonitor;

	return TRUE;
}

void usage(const char* arg0) {
	fprintf(stderr, "Usage: %s REGISTER VALUE\n", arg0);
	fprintf(stderr, "  both fields may be decimal numbers or 0x prefixed hexadecimal\n");
}

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments\n");
		usage(argv[0]);
		return 1;
	}

	int arg_register = strtol(argv[1], NULL, 0);
	int arg_value = strtol(argv[2], NULL, 0);

	HMONITOR monitor = NULL;
	struct _PHYSICAL_MONITOR physical;

	if (!EnumDisplayMonitors(NULL, NULL, monitor_enum, (LPARAM)&monitor)) {
		fprintf(stderr, "EnumDisplayMonitors failed\n");
		return 1;
	}

	if (!GetPhysicalMonitorsFromHMONITOR(monitor, 1, &physical)) {
		fprintf(stderr, "GetPhysicalMonitorsFromHMONITOR failed\n");
		return 1;
	}

	if (!SetVCPFeature(physical.hPhysicalMonitor, arg_register, arg_value)) {
		fprintf(stderr, "SetVCPFeature failed\n");
		return 1;
	}

	return 0;
}
