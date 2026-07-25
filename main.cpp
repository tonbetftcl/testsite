#include "MTR/Main.h"
#include "MTR/json.hpp"
#include "MTR/Items.h"
#include "MTR/enc.h"
#include "MTR/Vector3.hpp"
#include "MTR/font_awesome_6.h"
#include "MTR/Icon.h"
#include "MTR/Menu.h"
#include "MTR/OPPOSans-H.h"
#include "MTR/QuestrialRegular.h"
#include "MTR/roboto.h"
#include "MTR/Font.h"
#include "MTR/base64/base64.h"
#include "MTR/imgui/imgui.h"
#include "MTR/imgui/imgui_internal.h"
#include "MTR/imgui/backends/imgui_impl_android.h"
#include "MTR/imgui/backends/imgui_impl_opengl3.h"
#include "MTR/imgui/backends/android_native_app_glue.h"
#include "STR/skCrypter.h"
#include "STR/virtual_keyboard.h"
#include "STR/imgui_notify.h"
#include "STR/正楷.h"
#include "STR/black.h"
#include "STR/semibold.h"
#include "STR/bold.h"
#include "STR/LightFont.h"
#include "Bypass.h"
#include "Login.cpp"
#include "SKIN/skin.h"
#include "SKIN/skin_data.h"
ImFont *GetBoldFont;
ImFont *Icon;
#include "MTR/Image.hpp"
#include "SDK.hpp"
#include "MTR/Dobby/include/dobby.h"
using namespace SDK;
static void DrawDotLabel(const char* label, ImU32 col, float dotRadius = 8.0f, float spacing = 8.0f)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 cur = ImGui::GetCursorScreenPos();
    float y_center = cur.y + ImGui::GetFontSize() * 0.5f;
    ImVec2 dot_pos = ImVec2(cur.x + dotRadius, y_center);
    dl->AddCircleFilled(dot_pos, dotRadius, col);
    ImGui::SetCursorScreenPos(ImVec2(cur.x + dotRadius * 2 + spacing, cur.y));
    ImGui::TextUnformatted(label);
    ImVec2 after = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(after.x + 6.0f, cur.y)); 
}
static std::string GetConfigPath() {
    const char* paths[] = {
        "/storage/emulated/0/Android/data/com.tencent.ig/files/config.ini",
        "/storage/emulated/0/Android/data/com.pubg.krmobile/files/config.ini",
        "/storage/emulated/0/Android/data/com.vng.pubgmobile/files/config.ini",
        "/storage/emulated/0/Android/data/com.rekoo.pubgm/files/config.ini",
    };
    for (auto& p : paths) {
        if (FILE* f = fopen(p, "r")) { fclose(f); return p; }
    }
    return paths[0];
}
static void WriteConfig(const std::string& key, int value) {
    std::string path = GetConfigPath();
    
    std::string content;
    if (FILE* f = fopen(path.c_str(), "r")) {
        char buf[4096]; size_t n;
        while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
            content.append(buf, n);
        fclose(f);
    }
    std::string entry = key + "=" + std::to_string(value) + "\n";
    size_t pos = content.find(key + "=");
    if (pos != std::string::npos) {
        size_t end = content.find('\n', pos);
        content.replace(pos, end - pos, key + "=" + std::to_string(value));
    } else {
        content += entry;
    }
    if (FILE* f = fopen(path.c_str(), "w")) {
        fwrite(content.c_str(), 1, content.size(), f);
        fclose(f);
    }
}
ASTExtraPlayerCharacter* BULLET_HD() {
ASTExtraPlayerCharacter *result = nullptr;
float max = std::numeric_limits<float>::infinity();

}
auto start = std::chrono::steady_clock::now();
ImFont *QuestrialRegular;
using namespace SDK;
using on_change_callback = void (*)(int);
bool UpdateClothSkin(UCharacterAvatarComponent2 *);
using on_change_callback = void (*)(int);
ASTExtraVehicleBase *lastVehicle = NULL;
bool isModded = false;
bool isLoggedIn = false;
static DWORD Last_Gun_Used_To_Kill = 0;
static DWORD Current_Weapon = 0;
void logToFile(const char* format, ...) {
    FILE *logFile = fopen("/sdcard/hook_log.txt", "a");
    if (logFile == NULL) return;
    va_list args;
    va_start(args, format);
    vfprintf(logFile, format, args);
    va_end(args);
    fprintf(logFile, "\n");
    fclose(logFile);
}
static std::string package_name = "";
int OnRep_ItemListNet_Index = -1;
int ReceiveDrawHUD_Index = -1;
int OnRep_AvatarMeshChanged_Index = -1;
int OnRep_BodySlotStateChanged_Index = -1;
int GetItemAvatarHandle_Index = -1;
int CreateBattleItemHandle_Index = -1;
int CreateWeaponAndChangeSkin_Index = -1;
// If you need anything, don't hesitate to contact us. @VP_IZ
int DeadBoxAvatarComponent_Index = -1;
int DeadBoxAvatarComponent_GetLuaFilePath_Index = -1;
int total = 0;
int skipped = 0;
int doing = 0;
int GetPostRenderIndex() {
return (200 - 66);
}
using on_change_callback = void (*)(int);
namespace Setting {
    inline float nsize = 12.0f;
    inline int weaponsize = 12;
    inline int dissize = 12;
    inline int Test = 0;
    inline float pbonesize = 1.0f; 
    inline float plinesize = 1.0f;
    inline ImVec4 WeaponColor = ImVec4(1.000f, 1.000f, 0.000f, 1.000f);
}
namespace SDK {
    namespace Color {
        ImVec4 nam = ImVec4(1.000f, 1.000f, 0.000f, 1.000f);
        ImVec4 nam_border = ImVec4(0.000f, 0.000f, 0.000f, 1.000f);
        ImVec4 skelec = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
        ImVec4 playerline = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
        ImVec4 enemy = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
        ImVec4 HPP = ImVec4(1.000f, 1.000f, 0.000f, 1.000f);
        ImVec4 vehicle = ImVec4(1.000f, 1.000f, 0.000f, 1.000f);
    }
}

namespace Active
{
  inline int SkinCarDefault = 0;
  inline int SkinCarMod = 0;
  inline int SkinCarNew = 0;
}
#define BOX_PADDING 5.f

#define COLOR_BLACK FLinearColor(0, 0, 0, 1.f)
#define COLOR_WHITE FLinearColor(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED FLinearColor(1.f, 0, 0, 1.f)
#define COLOR_CAR FLinearColor(1.f, 0.5f, 1.f, 1.f)
#define COLOR_GREEN FLinearColor(0, 0.5f, 0, 1.f)
#define COLOR_ORANGE FLinearColor(1.f, 0.4f, 0, 1.f)
#define COLOR_YELLOW FLinearColor(1.f, 1.f, 0, 1.f)
#define COLOR_LIME FLinearColor(0, 1.f, 0, 1.f)
#define COLOR_BLUE FLinearColor(0, 0, 1.f, 1.f)
#define COLOR_THISTLE FLinearColor(1.0f, 0.74f, 0.84f, 1.0f)
#define MRB(x) ((float)(x) * (float)(IM_PI / 180.f))
static int WideValues = false;

bool WideView;

UObject *GetObjectByClass(UClass *Class, bool Default) {
auto objects = UObject::GetGlobalObjects();
const std::string defaultStr = "Default";

for (int i = 0; i < objects.Num(); i++) {
auto object = objects.GetByIndex(i);
if (!object || !object->IsA(Class)) {
continue;
}

auto objectName = object->GetFullName();
bool hasDefault = objectName.find(defaultStr) != std::string::npos;

if ((Default && hasDefault) || (!Default && !hasDefault)) {
return object;
}}
return nullptr;
}


static std::unordered_set<uint32_t> AlreadyChangedSet;
uintptr_t GetVirtualFunctionAddress(uintptr_t clazz, uintptr_t index)
{
    if (!clazz)
    {
        return 0;
    }
    uintptr_t vtablePtr = *(uintptr_t*)clazz;
    if (!vtablePtr)
    {
        return 0;
    }
    // Ensure index is within bounds of the vtable
    if (index < 0)
    {
        return 0;
    }
    return *((uintptr_t*)vtablePtr + index);
}
void ChangeItemAVc(uintptr_t thiz, int InItemID)
{
    if (thiz)
    {
        auto PrechangeitemAvatar_addr = GetVirtualFunctionAddress(thiz, 188); // vtable idx
        if (PrechangeitemAvatar_addr)
        {
            return ((void (*)(uintptr_t, int, bool))PrechangeitemAvatar_addr)(thiz, InItemID, true);
        }
    }
}

template <class T>
TArray<AActor *> GetAllActors1(UWorld *GWorld)
{
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *)gGameplayStatics->StaticClass();
    TArray<AActor *> Actors2;

    if (GWorld)
    {
        gGameplayStatics->GetAllActorsOfClass((UObject *)GWorld, T::StaticClass(), &Actors2);
        return Actors2;
    }
    return Actors2;
}

struct VehicleData
{
    const char *Name;
    FVector2D Pos;
    float Distance;
    int HP;
    int Fuel;
    float Velocity;
};

struct ItemData
{
    std::string Name;
    FVector2D Pos;
    float Distance;
    ImColor Color;
};
struct BoxData
{
    std::string Name;
    FVector2D Pos;
    float Distance;
};

struct GrenadeData
{
    std::string Name;
    FVector2D Pos;
    float Distance;
    float timeout;
};

std::vector<ASTExtraPlayerCharacter *> _playerData, playerData;
std::vector<VehicleData> vehicleData = {};
std::vector<VehicleData> _vehicleData = {};
std::vector<ItemData> _itemData = {};
std::vector<BoxData> boxData = {};
std::vector<BoxData> _boxData = {};
std::vector<GrenadeData> grenadeData = {};
std::vector<GrenadeData> _grenadeData = {};

//

std::time_t string_to_timet(std::string timestamp)
{
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}


bool IsPtrValid(void *addr) {
    if (!addr) {
        return false;
    }
    static int fd = -1;
    if (fd == -1) {
        fd = open("/dev/random", O_WRONLY);
    }
    return write(fd, addr, 4) >= 0;
}

ASTExtraPlayerCharacter *g_localPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;
struct sRegion
{
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;
bool isObjectInvalid(UObject *obj)
{

    if (!IsPtrValid(obj))
    {
        return true;
    }
    if (!IsPtrValid(obj->ClassPrivate))
    {
        return true;
    }
    if (obj->InternalIndex <= 0)
    {
        return true;
    }
    if (obj->NamePrivate.ComparisonIndex <= 0)
    {
        return true;
    }
    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4)
    {
        return true;
    }
    //    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
    //        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
    //        return true;
    //    }
    return false;
}

std::string GetPackageName()
{
    FILE *f = fopen("/proc/self/cmdline", "rb");
    if (f)
    {
        char buf[64] = {0};
        fread(buf, sizeof(char), 63, f);
        fclose(f);
        return std::string(buf);
    }
    return "";
}

#include "SKIN/SkinMain.h"

bool draw_thread = true, proc_thread = true, mem_thread = true;

float text_size = 15.f;

static std::vector<AActor *> Actors = {};

void DrawFilledRectangle(float X, float Y, float Width, float Height, ImColor Color)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + Width, Y + Height), Color);
}

void DrawLine(float X1, float Y1, float X2, float Y2, ImColor Color, float Thickness = 1)
{
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X1, Y1), ImVec2(X2, Y2), Color, Thickness);
}

void CornerBox(float x, float y, float w, float h, float thickness, float cornered, ImColor color)
{
    // Left Top
    DrawLine(x, y, x + (w * cornered), y, color, thickness);
    DrawLine(x, y, x, y + (h * cornered), color, thickness);
    // Left Bottom
    DrawLine(x, y + h, x + (w * cornered), y + h, color, thickness);
    DrawLine(x, y + h, x, (y + h) - (h * cornered), color, thickness);
    // Right Top
    DrawLine(x + w, y, (x + w) - (w * cornered), y, color, thickness);
    DrawLine(x + w, y, x + w, y + (h * cornered), color, thickness);
    // Right Bottom
    DrawLine(x + w, y + h, (x + w) - (w * cornered), y + h, color, thickness);
    DrawLine(x + w, y + h, x + w, (y + h) - (h * cornered), color, thickness);
}

void DrawBorderString(ImFont *pFont, float FontSize, std::string Text, float X, float Y, ImColor Color, bool Center = false)
{
    ImDrawList *drawList = ImGui::GetBackgroundDrawList();
    if (Center)
    {
        ImVec2 textSize = pFont->CalcTextSizeA(FontSize, FLT_MAX, 0.0f, Text.c_str());
        X -= textSize.x / 2.0f;
    }

    ImVec4 borderCol = ImVec4(0, 0, 0, 200.0f / 255.0f);

    drawList->AddText(pFont, FontSize, ImVec2(X - 1, Y), ImColor(borderCol), Text.c_str());
    drawList->AddText(pFont, FontSize, ImVec2(X + 1, Y), ImColor(borderCol), Text.c_str());
    drawList->AddText(pFont, FontSize, ImVec2(X, Y - 1), ImColor(borderCol), Text.c_str());
    drawList->AddText(pFont, FontSize, ImVec2(X, Y + 1), ImColor(borderCol), Text.c_str());

    drawList->AddText(pFont, FontSize, ImVec2(X, Y), Color, Text.c_str());
}

#include "MTR/Setting.h"

enum class EType : int
{
    BOT,
    BULLET
};

enum class EAim : int
{
    DISTANCE,
    CROSS_HAIR
};

enum class EAimTarget : int
{
    HEAD,
    CHEST,
    BODY,
    NEAREST
};

enum EAimTrigger
{
    NONE,
    SHOOTING,
    SCOPING,
    BOTH,
    ANY
};

namespace config_t
{

    namespace protection
    {
        bool spownisland{false};
    }

    namespace esp
    {
        namespace visual
        {
            bool bARNear = false;
            bool bLine{false};
            bool bBox{false};
            bool bAlert{false};
            bool bTeamID{false};
            bool bPlayerName{false};
            bool bDistance{false};
            bool bHealth{false};
            bool bSungDich{false};
            bool bSkeleton{false};
            bool bHeadDots{false};

            bool bIgnoreAI{false};
            bool RadarXY{false};
            bool MatchInfo{false};
            bool TRIANGLE{false};
            bool AR{false};
            bool Enemy{false};
            bool OpenAllAlert{false};
            bool bHud{false};
            //
            bool bEnemyWeapon{false};
            bool bVehicle{false};
            bool bItem{false};
            bool bShowAround{false};
            bool bEnemyAiming{false};
       //     bool SkinDumpss{false};

            bool bypass{false};
        }

    }

    namespace memory
    {

        bool ipad{false};
        bool lessricoil{false};
        bool tamcong = false;
        bool Aimlock = false;
        bool IpadView = false;
        bool hdr;

    }

    namespace aim
    {
        bool enabled{false};
        float fovSize{70.f};
        int segment{0};
        EAim aim_by{EAim::CROSS_HAIR};
        EType aim_type{EType::BOT};
        EAimTarget type_target{EAimTarget::HEAD};
        EAimTrigger type_trigger{EAimTrigger::ANY};
        bool bIgnoreKnocked{false};
        bool bVisCheck{true};
        bool bSmooth{false};
        bool bShowTarget{true};
        bool bFixFakeDamge{false};
        float smoothness{1.f};
        float DisAim = 70.0f;
        bool protection{false};
        float protection_value{5.f};
        bool Smooth_comparison{false};
        float Smooth_comparison_value{1.f};
        bool recoil_comparison{false};
        float recoil_comparison_value{1.2f};
    }

};
bool show;
bool HideRecord;
bool Funny;
bool Textborder;

bool saveConfig()
{
    nlohmann::json settings;
    
    // Visual Settings
    settings["visual"]["bLine"] = config_t::esp::visual::bLine;
    settings["visual"]["bBox"] = config_t::esp::visual::bBox;
    settings["visual"]["bAlert"] = config_t::esp::visual::bBox;
    settings["visual"]["bTeamID"] = config_t::esp::visual::bTeamID;
    settings["visual"]["bPlayerName"] = config_t::esp::visual::bPlayerName;
    settings["visual"]["bDistance"] = config_t::esp::visual::bDistance;
    settings["visual"]["bHealth"] = config_t::esp::visual::bHealth;
    settings["visual"]["bSkeleton"] = config_t::esp::visual::bSkeleton;
    settings["visual"]["bAlert"] = config_t::esp::visual::bAlert;
    settings["visual"]["bIgnoreAI"] = config_t::esp::visual::bIgnoreAI;
    settings["visual"]["RadarXY"] = config_t::esp::visual::RadarXY;
    settings["visual"]["MatchInfo"] = config_t::esp::visual::MatchInfo;
    settings["visual"]["Enemy"] = config_t::esp::visual::Enemy;
    settings["visual"]["TRIANGLE"] = config_t::esp::visual::TRIANGLE;
    settings["visual"]["bEnemyWeapon"] = config_t::esp::visual::bEnemyWeapon;
    settings["visual"]["bVehicle"] = config_t::esp::visual::bVehicle;
    settings["visual"]["OpenAllAlert"] = config_t::esp::visual::OpenAllAlert;
    settings["visual"]["bSungDich"] = config_t::esp::visual::bSungDich;
    settings["visual"]["bARNear"] = config_t::esp::visual::bARNear;
    settings["visual"]["bItem"] = config_t::esp::visual::bItem;
    settings["visual"]["bShowAround"] = config_t::esp::visual::bShowAround;
    settings["visual"]["bEnemyAiming"] = config_t::esp::visual::bEnemyAiming;
   
    settings["visual"]["bGrenadeLine"] = config_t::esp::visual::OpenAllAlert;

    settings["memory"]["ipad"] = config_t::memory::ipad;
    settings["memory"]["lessricoil"] = config_t::memory::lessricoil;
    settings["memory"]["tamcong"] = config_t::memory::tamcong;
    settings["memory"]["hdr"] = config_t::memory::hdr;
    settings["memory"]["WideView"] = WideView;

    settings["aim"]["enabled"] = config_t::aim::enabled;
    settings["aim"]["fovSize"] = config_t::aim::fovSize;
    settings["aim"]["segment"] = config_t::aim::segment;
    settings["aim"]["aim_by"] = config_t::aim::aim_by;
    settings["aim"]["aim_type"] = config_t::aim::aim_type;
    settings["aim"]["type_target"] = config_t::aim::type_target;
    settings["aim"]["type_trigger"] = config_t::aim::type_trigger;
    settings["aim"]["bIgnoreKnocked"] = config_t::aim::bIgnoreKnocked;
    settings["aim"]["bVisCheck"] = config_t::aim::bVisCheck;
    settings["aim"]["bShowTarget"] = config_t::aim::bShowTarget;
    settings["aim"]["bSmooth"] = config_t::aim::bSmooth;
    settings["aim"]["DisAim"] = config_t::aim::DisAim;
    settings["aim"]["smoothness"] = config_t::aim::smoothness;
    settings["aim"]["protection"] = config_t::aim::protection;
    settings["aim"]["protection_value"] = config_t::aim::protection_value;
    settings["aim"]["recoil_comparison"] = config_t::aim::recoil_comparison;
    settings["aim"]["recoil_comparison_value"] = config_t::aim::recoil_comparison_value;
    
    // Skin Main Settings
    settings["skin"]["bEnable"] = skin.bEnable;
    settings["skin"]["bGunSkin"] = skin.bGunSkin;
    settings["skin"]["bClothSkin"] = skin.bClothSkin;
    settings["skin"]["bVehicleSkin"] = skin.bVehicleSkin;
    settings["skin"]["bKillMsg"] = skin.bKillMsg;
    settings["skin"]["bDeadbox"] = skin.bDeadbox;
    

    settings["skin"]["gun"]["M16A4"] = skin.gun->M16A4;
    settings["skin"]["gun"]["M416"] = skin.gun->M416;
    settings["skin"]["gun"]["AKM"] = skin.gun->AKM;
    settings["skin"]["gun"]["SCARL"] = skin.gun->SCARL;
    settings["skin"]["gun"]["AUG"] = skin.gun->AUG;
    settings["skin"]["gun"]["M762"] = skin.gun->M762;
    settings["skin"]["gun"]["GROZA"] = skin.gun->GROZA;
    settings["skin"]["gun"]["HONEY"] = skin.gun->HONEY;
    settings["skin"]["gun"]["ACE32"] = skin.gun->ACE32;
    settings["skin"]["gun"]["QBZ"] = skin.gun->QBZ;
    settings["skin"]["gun"]["UMP45"] = skin.gun->UMP45;
    settings["skin"]["gun"]["UZI"] = skin.gun->UZI;
    settings["skin"]["gun"]["VECTOR"] = skin.gun->VECTOR;
    settings["skin"]["gun"]["TOMMY"] = skin.gun->TOMMY;
    settings["skin"]["gun"]["KAR98"] = skin.gun->KAR98;
    settings["skin"]["gun"]["M24"] = skin.gun->M24;
    settings["skin"]["gun"]["AWM"] = skin.gun->AWM;
    settings["skin"]["gun"]["AMR"] = skin.gun->AMR;
    settings["skin"]["gun"]["MK14"] = skin.gun->MK14;
    settings["skin"]["gun"]["MINI14"] = skin.gun->MINI14;
    settings["skin"]["gun"]["M249"] = skin.gun->M249;
    settings["skin"]["gun"]["DP28"] = skin.gun->DP28;
    settings["skin"]["gun"]["MG3"] = skin.gun->MG3;
    settings["skin"]["gun"]["PAN"] = skin.gun->PAN;
    settings["skin"]["gun"]["S12K"] = skin.gun->S12K;
    settings["skin"]["gun"]["DBS"] = skin.gun->DBS;
    settings["skin"]["gun"]["XM1014"] = skin.gun->XM1014;
    settings["skin"]["gun"]["P90"] = skin.gun->P90;
    
    // Other Settings
  //  settings["other"]["AntiBan"] = AntiBan;
   // settings["other"]["SkinDumpss"] = SkinDumpss;

    auto package_name = GetPackageName();

    std::ofstream configf("/sdcard/Android/data/" + package_name + "/files/MTMOD.json");
    if (configf.is_open())
    {
        configf << settings.dump(4);
        configf.close();
        return true;
    }
    else
    {
        LOGE("Can't save setting file: %s", package_name.c_str());
        return false;
    }
}

bool loadConfig()
{
    auto package_name = GetPackageName();

    std::ifstream file1("/sdcard/Android/data/" + package_name + "/files/MTMOD.json");
    if (file1.is_open())
    {
        json settings = json::parse(file1);
        
        // Visual Settings
        config_t::esp::visual::bLine = settings["visual"]["bLine"];
        config_t::esp::visual::bBox = settings["visual"]["bBox"];
        config_t::esp::visual::bBox = settings["visual"]["bAlert"];
        config_t::esp::visual::bTeamID = settings["visual"]["bTeamID"];
        config_t::esp::visual::bPlayerName = settings["visual"]["bPlayerName"];
        config_t::esp::visual::bDistance = settings["visual"]["bDistance"];
        config_t::esp::visual::bHealth = settings["visual"]["bHealth"];
        config_t::esp::visual::bSkeleton = settings["visual"]["bSkeleton"];
        config_t::esp::visual::bAlert = settings["visual"]["bAlert"];
        config_t::esp::visual::bIgnoreAI = settings["visual"]["bIgnoreAI"];
        config_t::esp::visual::RadarXY = settings["visual"]["RadarXY"];
        config_t::esp::visual::MatchInfo = settings["visual"]["MatchInfo"];
        config_t::esp::visual::Enemy = settings["visual"]["Enemy"];
        config_t::esp::visual::TRIANGLE = settings["visual"]["TRIANGLE"];
        config_t::esp::visual::bEnemyWeapon = settings["visual"]["bEnemyWeapon"];
        config_t::esp::visual::bVehicle = settings["visual"]["bVehicle"];
        config_t::esp::visual::OpenAllAlert = settings["visual"]["OpenAllAlert"];
        config_t::esp::visual::bARNear = settings["visual"]["bARNear"];
        config_t::esp::visual::bItem = settings["visual"]["bItem"];
        config_t::esp::visual::bShowAround = settings["visual"]["bShowAround"];
        config_t::esp::visual::bSungDich = settings["visual"]["bSungDich"];
        config_t::esp::visual::bEnemyAiming = settings["visual"]["bEnemyAiming"];
        config_t::esp::visual::OpenAllAlert = settings["visual"]["bGrenadeLine"];
       
        // Memory Settings
        config_t::memory::ipad = settings["memory"]["ipad"];
        config_t::memory::lessricoil = settings["memory"]["lessricoil"];
        config_t::memory::tamcong = settings["memory"]["tamcong"];
        config_t::memory::hdr = settings["memory"]["hdr"];
        WideView = settings["memory"]["WideView"];
      //  WideValue = settings["memory"]["WideValue"];
        
        // Aim Settings
        config_t::aim::enabled = settings["aim"]["enabled"];
        config_t::aim::fovSize = settings["aim"]["fovSize"];
        config_t::aim::segment = settings["aim"]["segment"];
        config_t::aim::aim_by = settings["aim"]["aim_by"];
        config_t::aim::aim_type = settings["aim"]["aim_type"];
        config_t::aim::type_target = settings["aim"]["type_target"];
        config_t::aim::type_trigger = settings["aim"]["type_trigger"];
        config_t::aim::bIgnoreKnocked = settings["aim"]["bIgnoreKnocked"];
        config_t::aim::bVisCheck = settings["aim"]["bVisCheck"];
        config_t::aim::bShowTarget = settings["aim"]["bShowTarget"];
        config_t::aim::bSmooth = settings["aim"]["bSmooth"];
        config_t::aim::DisAim = settings["aim"]["DisAim"];
        config_t::aim::smoothness = settings["aim"]["smoothness"];
        config_t::aim::protection = settings["aim"]["protection"];
        config_t::aim::protection_value = settings["aim"]["protection_value"];
        config_t::aim::recoil_comparison = settings["aim"]["recoil_comparison"];
        config_t::aim::recoil_comparison_value = settings["aim"]["recoil_comparison_value"];
        
        // Skin Main Settings
        skin.bEnable = settings["skin"]["bEnable"];
        skin.bGunSkin = settings["skin"]["bGunSkin"];
        skin.bClothSkin = settings["skin"]["bClothSkin"];
        skin.bVehicleSkin = settings["skin"]["bVehicleSkin"];
        skin.bKillMsg = settings["skin"]["bKillMsg"];
        skin.bDeadbox = settings["skin"]["bDeadbox"];
        
       // Cloth Settings
        skin.cloth->SHIRT = settings["skin"]["cloth"]["SHIRT"];
        skin.cloth->HAT = settings["skin"]["cloth"]["HAT"];
        skin.cloth->FACE = settings["skin"]["cloth"]["FACE"];
        skin.cloth->MASK = settings["skin"]["cloth"]["MASK"];
        skin.cloth->GLOVES = settings["skin"]["cloth"]["GLOVES"];
        skin.cloth->PANT = settings["skin"]["cloth"]["PANT"];
        skin.cloth->SHOE = settings["skin"]["cloth"]["SHOE"];
        skin.cloth->PARACHUTE = settings["skin"]["cloth"]["PARACHUTE"];
        skin.cloth->GLIDER = settings["skin"]["cloth"]["GLIDER"];
        skin.cloth->BACKPACK = settings["skin"]["cloth"]["BACKPACK"];
        skin.cloth->BACKPACK1 = settings["skin"]["cloth"]["BACKPACK1"];
        skin.cloth->BACKPACK2 = settings["skin"]["cloth"]["BACKPACK2"];
        skin.cloth->BACKPACK3 = settings["skin"]["cloth"]["BACKPACK3"];
        skin.cloth->HELMET = settings["skin"]["cloth"]["HELMET"];
        skin.cloth->HELMET1 = settings["skin"]["cloth"]["HELMET1"];
        skin.cloth->HELMET2 = settings["skin"]["cloth"]["HELMET2"];
        skin.cloth->HELMET3 = settings["skin"]["cloth"]["HELMET3"];
        skin.cloth->EMOTE1 = settings["skin"]["cloth"]["EMOTE1"];
        skin.cloth->EMOTE2 = settings["skin"]["cloth"]["EMOTE2"];
        skin.cloth->EMOTE3 = settings["skin"]["cloth"]["EMOTE3"];

        // Vehicle Settings
        skin.vehicle->UAZ = settings["skin"]["vehicle"]["UAZ"];
        skin.vehicle->MOTOR = settings["skin"]["vehicle"]["MOTOR"];
        skin.vehicle->DACIA = settings["skin"]["vehicle"]["DACIA"];
        skin.vehicle->COUPE = settings["skin"]["vehicle"]["COUPE"];
        skin.vehicle->MIRADO = settings["skin"]["vehicle"]["MIRADO"];
        skin.vehicle->BUGGY = settings["skin"]["vehicle"]["BUGGY"];
        
        // Gun Settings
        skin.gun->M16A4 = settings["skin"]["gun"]["M16A4"];
        skin.gun->M416 = settings["skin"]["gun"]["M416"];
        skin.gun->AKM = settings["skin"]["gun"]["AKM"];
        skin.gun->SCARL = settings["skin"]["gun"]["SCARL"];
        skin.gun->AUG = settings["skin"]["gun"]["AUG"];
        skin.gun->M762 = settings["skin"]["gun"]["M762"];
        skin.gun->GROZA = settings["skin"]["gun"]["GROZA"];
        skin.gun->HONEY = settings["skin"]["gun"]["HONEY"];
        skin.gun->ACE32 = settings["skin"]["gun"]["ACE32"];
        skin.gun->QBZ = settings["skin"]["gun"]["QBZ"];
        skin.gun->UMP45 = settings["skin"]["gun"]["UMP45"];
        skin.gun->UZI = settings["skin"]["gun"]["UZI"];
        skin.gun->VECTOR = settings["skin"]["gun"]["VECTOR"];
        skin.gun->TOMMY = settings["skin"]["gun"]["TOMMY"];
        skin.gun->KAR98 = settings["skin"]["gun"]["KAR98"];
        skin.gun->M24 = settings["skin"]["gun"]["M24"];
        skin.gun->AWM = settings["skin"]["gun"]["AWM"];
        skin.gun->AMR = settings["skin"]["gun"]["AMR"];
        skin.gun->MK14 = settings["skin"]["gun"]["MK14"];
        skin.gun->MINI14 = settings["skin"]["gun"]["MINI14"];
        skin.gun->M249 = settings["skin"]["gun"]["M249"];
        skin.gun->DP28 = settings["skin"]["gun"]["DP28"];
        skin.gun->MG3 = settings["skin"]["gun"]["MG3"];
        skin.gun->PAN = settings["skin"]["gun"]["PAN"];
        skin.gun->S12K = settings["skin"]["gun"]["S12K"];
        skin.gun->DBS = settings["skin"]["gun"]["DBS"];
        skin.gun->XM1014 = settings["skin"]["gun"]["XM1014"];
        skin.gun->P90 = settings["skin"]["gun"]["P90"];
        
        // Other Settings
     //   AntiBan = settings["other"]["AntiBan"];
       // SkinDumpss = settings["other"]["SkinDumpss"];

        file1.close();
        return true;
    }
    else
    {
        LOGE("Can't load setting file: %s", package_name.c_str());
        return false;
    }
}

namespace Data {
    SDK::ASTExtraPlayerCharacter *localPlayer = nullptr;
    SDK::ASTExtraPlayerController *localController = nullptr;
    static SDK::ASTExtraLobbyCharacter* localLobby = nullptr;
    namespace Cheat {
    float Velocityop = 0.f;
    float Altitute = 0.f;
    float travlled = 0;
    uintptr_t UE4;
    uintptr_t Anogs;
    android_app* App = 0;
    } namespace Offset { 
    
    //Skin Weapon!!
    DWORD NetAvatarSyncData = 0x3e8; // NetAvatarSyncData* NetAvatarData
    uintptr_t DeadBoxAvatarComponent_BP_C = 0x718; // DeadBoxAvatarComponent_BP_C

   }
}
#define GNativeAndroidApp_Offset 0xec732a8
#define GNames_Offset 0x8939470
#define GUObject_Offset 0xef3b3f0
#define GetActorArray_offset 0xa6ca440
#define Actors_Offset 0xA0

int languages;

uintptr_t GetBaseAddress(const char *name) {
    uintptr_t base = 0;
    char line[512];

    FILE *f = fopen(("/proc/self/maps"), ("r"));

    if (!f) {
        return 0;
    }
    while (fgets(line, sizeof line, f)) {
        uintptr_t tmpBase;
        char tmpName[256];
        if (sscanf(line, "%" PRIXPTR "-%*" PRIXPTR "%*s %*s %*s %*s %s", &tmpBase, tmpName) > 0) {
            if (!strcmp(basename(tmpName), name)) {
                base = tmpBase;
                break;
            }
        }
    }
    fclose(f);
    return base;
}

#if defined(_arm_)
int vm_readv_syscall = 376;
int vm_writev_syscall = 377;
#elif defined(_aarch64_)
int vm_readv_syscall = 270;
int vm_writev_syscall = 271;
#elif defined(_i386_)
int vm_readv_syscall = 347;
int vm_writev_syscall = 348;
#else
int vm_readv_syscall = 310;
int vm_writev_syscall = 311;
#endif

#define TEXT(s) L##s



ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,
                  const struct iovec *__remote_iov, unsigned long __remote_iov_count,
                  unsigned long __flags, bool iswrite)
{
    return syscall((iswrite ? vm_writev_syscall : vm_readv_syscall), __pid,
                   __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

struct PvmResult
{
    bool success;
    uintptr_t addr;
};

PvmResult pvm(void *address, void *buffer, size_t size, bool iswrite)
{
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;

    struct PvmResult result;
    result.success = false;
    result.addr = 0;

    if (getpid() < 0)
    {
        return result;
    }

    ssize_t bytes = process_v(getpid(), local, 1, remote, 1, 0, iswrite);

    if (bytes == size)
    {
        result.success = true;
        result.addr = reinterpret_cast<uintptr_t>(remote[0].iov_base);
    }
    return result;
}

bool vm_readv(long int address, void *buffer, size_t size)
{
    struct PvmResult result = pvm(reinterpret_cast<void *>(address), buffer, size, false);
    return result.success;
}

long int getint(long int addr)
{
    if (addr < 0xFFFFFF)
    {
        return 0;
    }
    long int var[4] = {0};
    memset(var, 0, 4);
    vm_readv(addr, var, 4);
    return var[0];
}

uintptr_t getAddr(uintptr_t addr, bool showAddr = false)
{
    if (addr < 0xFFFFFF)
    {
        return 0;
    }
    uintptr_t var[4] = {0};
    memset(var, 0, sizeof(var));
    if (showAddr)
    {
        struct PvmResult result = pvm(reinterpret_cast<void *>(addr), var, sizeof(var), false);

        if (result.success)
        {
            // encLog("Read successful. Address: %p", result.addr);
            return result.addr;
        }
    }
    vm_readv(addr, var, sizeof(var));
    return var[0];
}

using json = nlohmann::json;

json itemData;
json items_data;

uintptr_t UE4, ANORT, g_UE4, GCLOUD;

bool volumeUpPressed = false;
bool HideWindow = true;
bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1, Radar, RadarX = 320, RadarY = 255;

std::map<int, bool> Items;
std::map<int, float *> ItemColors;

int32_t ToColor(float *col)
{
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *)(col));
}

#define CREATE_COLOR(r, g, b, a) new float[4]{(float)r, (float)g, (float)b, (float)a};

#define LAWNGREEN(alpha) \
    ImColor { 124, 252, 0, alpha }
#define YELLOW(alpha) \
    ImColor { 255, 255, 0, alpha }

ImColor color;
ImColor AM;

template <typename T>
void Write(uintptr_t addr, T value)
{
    WriteAddr((void *)addr, &value, sizeof(T));
}

static UEngine *GEngine = 0;
UWorld *GetWorld()
{
    while (!GEngine)
    {
        GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1");
        sleep(1);
    }
    if (GEngine)
    {
        auto ViewPort = GEngine->GameViewport;
        if (ViewPort)
        {
            return ViewPort->World;
        }
    }
    return 0;
}

TNameEntryArray *GetGNames()
{
    return ((TNameEntryArray * (*)())(UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors()
{
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();
    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();
    struct GovnoArray
    {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};
    Actors = *(((GovnoArray * (*)(uintptr_t))(UE4 + GetActorArray_offset))(reinterpret_cast<uintptr_t>(PersistentLevel)));
    if (Actors.count <= 0)
    {
        return {};
    }
    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++)
    {
        auto Actor = *(uintptr_t *)(Actors.base + (i * sizeof(uintptr_t)));
        if (Actor)
        {
            actors.push_back(reinterpret_cast<AActor *const>(Actor));
        }
    }
    return actors;
}
template <class T>
void GetAllActors(std::vector<T *> &Actors)
{
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *)gGameplayStatics->StaticClass();
    auto GWorld = GetWorld();
    if (GWorld)
    {
        TArray<AActor *> Actors2;
        gGameplayStatics->GetAllActorsOfClass((UObject *)GWorld, T::StaticClass(), &Actors2);
        for (int i = 0; i < Actors2.Num(); i++)
        {
            Actors.push_back((T *)Actors2[i]);
        }
    }
}

std::string getObjectPath(UObject *Object)
{
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *)super->SuperStruct)
    {
        if (!s.empty())
            s += ".";
        s += super->NamePrivate.GetName();
    }
    return s;
}

#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(g_LocalController, w, true, s)

bool W2S2(FVector worldPos, FVector2D *screenPos)
{
    return g_LocalController->ProjectWorldLocationToScreen(worldPos, true, screenPos);
}

const char *GetVehicleName(ASTExtraVehicleBase *Vehicle)
{
    switch (Vehicle->VehicleShapeType)
    {
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
        return "Motorbike";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
        return "Dacia";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
        return "Mini Bus";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
        return "Pick Up";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
        return "Buggy";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
        return "UAZ";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
        return "PG117";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
        return "Aquarail";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
        return "Mirado";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
        return "Rony";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
        return "Scooter";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
        return "Snow Mobile";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
        return "Tuk Tuk";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
        return "Snow Bike";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
        return "Surf Board";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
        return "Snow Board";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
        return "Amphibious";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
        return "Lada Niva";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
        return "UAV";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
        return "Mega Drop";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
        return "Lamborghini";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
        return "Gold Mirado";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
        return "Big Foot";
        break;
    case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
        return "UH60";
        break;
    default:
        return "Vehicle";
        break;
    }
    return "Vehicle";
}

std::string GetLootName(APickUpListWrapperActor *Loot)
{
    switch (Loot->BoxType)
    {
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_TombBox:
        return "Tomb Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_AirDropBox:
        return "AirDrop Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_TreasureBox:
        return "Treasure Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_MonsterTombBox:
        return "Monster Tomb Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_VehicleBox:
        return "Vehicle Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_DeadRemainBox:
        return "Dead Remain Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_ResourceBox:
        return "Resource Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_LootBox:
        return "Loot Box";
        break;
    case EPickUpBoxType::EPickUpBoxType__EPickUpBoxType_MAX:
        return "MAX";
        break;
    default:
        return "Unknown";
        break;
    }
    return "Unknown";
}

#include <mutex>
std::mutex actors_mutex;
std::vector<AActor *> NecessaryActors; // Global variable

std::vector<AActor *> GetNecessaryActors()
{
    std::vector<AActor *> out = {};
    auto GWorld = GetWorld();
    auto Actors = *(((TArray<AActor *> * (*)(uintptr_t))(UE4 + GetActorArray_offset))(reinterpret_cast<uintptr_t>(GWorld->PersistentLevel)));
    for (int i = 0; i < Actors.Num(); i++)
    {
        auto Actor = Actors[i];
        if (Actor)
        {
            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()) ||
                Actor->IsA(ASTExtraVehicleBase::StaticClass()) ||
                Actor->IsA(ASTExtraGameStateBase::StaticClass()) ||
                Actor->IsA(ASTExtraGrenadeBase::StaticClass()) ||
                Actor->IsA(APickUpListWrapperActor::StaticClass()) ||
                Actor->IsA(APickUpWrapperActor::StaticClass()))
                out.push_back(Actor);
        }
    }
    return out;
}
#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))

void Line(ImDrawList *draw, FVector2D origin, FVector2D dest, ImColor color)
{
    draw->AddLine({origin.X, origin.Y}, {dest.X, dest.Y}, color, 1.0f);
}

void Box3D(ImDrawList *draw, FVector origin, FVector extends, ImColor col)
{
    origin.X -= extends.X / 2.f;
    origin.Y -= extends.Y / 2.f;
    origin.Z -= extends.Z / 2.f;

    FVector one = origin;
    FVector two = origin;
    two.X += extends.X;
    FVector tree = origin;
    tree.X += extends.X;
    tree.Y += extends.Y;
    FVector four = origin;
    four.Y += extends.Y;

    FVector five = one;
    five.Z += extends.Z;
    FVector six = two;
    six.Z += extends.Z;
    FVector seven = tree;
    seven.Z += extends.Z;
    FVector eight = four;
    eight.Z += extends.Z;

    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
        W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8))
    {

        Line(draw, s1, s2, col);
        Line(draw, s2, s3, col);
        Line(draw, s3, s4, col);
        Line(draw, s4, s1, col);

        Line(draw, s5, s6, col);
        Line(draw, s6, s7, col);
        Line(draw, s7, s8, col);
        Line(draw, s8, s5, col);

        Line(draw, s1, s5, col);
        Line(draw, s2, s6, col);
        Line(draw, s3, s7, col);
        Line(draw, s4, s8, col);
    }
}

void Box4Line(ImDrawList *draw, float thicc, int x, int y, int w, int h, int color)
{
    int iw = w / 4;
    int ih = h / 4;
    draw->AddRect(ImVec2(x, y), ImVec2(x + iw, y), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y), ImVec2(x + w, y), color, thicc);
    draw->AddRect(ImVec2(x, y), ImVec2(x, y + ih), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y), ImVec2(x + w - 1, y + ih), color, thicc);
    ;

    draw->AddRect(ImVec2(x, y + h), ImVec2(x + iw, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y + h), ImVec2(x + w, y + h), color, thicc);
    draw->AddRect(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thicc);
}

void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, int color)
{
    draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);
}

void VectorAnglesRadar(Vector3 &forward, FVector &angles)
{
    if (forward.X == 0.f && forward.Y == 0.f)
    {
        angles.X = forward.Z > 0.f ? -90.f : 90.f;
        angles.Y = 0.f;
    }
    else
    {
        angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
        angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
    }
    angles.Z = 0.f;
}

void RotateTriangle(std::array<Vector3, 3> &points, float rotation)
{
    const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
    for (auto &point : points)
    {
        point = point - points_center;
        const auto temp_x = point.X;
        const auto temp_y = point.Y;
        const auto theta = DEG2RAD(rotation);
        const auto c = cosf(theta);
        const auto s = sinf(theta);
        point.X = temp_x * c - temp_y * s;
        point.Y = temp_x * s + temp_y * c;
        point = point + points_center;
    }
}

FRotator ToRotator(FVector local, FVector target)
{
    FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);
    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);
    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float)3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float)3.14159265358979323846);
    newViewAngle.Roll = (float)0.f;
    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 100.0f;
    return newViewAngle;
}

FVector2D pushToScreenBorder(FVector2D Pos, FVector2D screen, int borders, int offset)
{
    int x = (int)Pos.X;
    int y = (int)Pos.Y;
    if ((borders & 1) == 1)
    {
        y = 0 - offset;
    }
    if ((borders & 2) == 2)
    {
        x = (int)screen.X + offset;
    }
    if ((borders & 4) == 4)
    {
        y = (int)screen.Y + offset;
    }
    if ((borders & 8) == 8)
    {
        x = 0 - offset;
    }
    return FVector2D(x, y);
}

int isOutsideSafezone(FVector2D pos, FVector2D screen)
{
    FVector2D mSafezoneTopLeft(screen.X * 0.04f, screen.Y * 0.04f);
    FVector2D mSafezoneBottomRight(screen.X * 0.96f, screen.Y * 0.96f);
    int result = 0;
    if (pos.Y < mSafezoneTopLeft.Y)
    {
        result |= 1;
    }
    if (pos.X > mSafezoneBottomRight.X)
    {
        result |= 2;
    }
    if (pos.Y > mSafezoneBottomRight.Y)
    {
        result |= 4;
    }
    if (pos.X < mSafezoneTopLeft.X)
    {
        result |= 8;
    }
    return result;
}

class FPSCounter
{
protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    long m_fpsinterval;

public:
    FPSCounter() : m_fps(0), m_fpscount(0), m_fpsinterval(0)
    {
    }

    void update()
    {
        m_fpscount++;

        if (m_fpsinterval < time(0))
        {
            m_fps = m_fpscount;

            m_fpscount = 0;
            m_fpsinterval = time(0) + 1;
        }
    }

    unsigned int get() const
    {
        return m_fps;
    }
};

FPSCounter fps;

void ClampAngles(FRotator &angles)
{
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;

    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;

    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}
bool isInsideFOV(int x, int y)
{
    if (!config_t::aim::fovSize)
        return true;

    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = config_t::aim::fovSize;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

bool isInsideFOVNearest(int x, int y, float fov)
{
    if (!config_t::aim::fovSize)
        return true;

    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = fov;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

inline bool IsBot(ASTExtraPlayerCharacter *player)
{
    std::string UID = player->PlayerUID.ToString();
    return UID.length() < 7;
}

ASTExtraPlayerCharacter *GetBestLineTarget()
{
    ASTExtraPlayerCharacter *Target = 0;
    float max = std::numeric_limits<float>::infinity();
    auto localPlayer = g_localPlayer;
    auto LocalController = g_LocalController;

    auto GWorld = GetWorld();
    if (!GWorld)
    {
        return 0;
    }
    if (!GWorld->PersistentLevel)
    {
        return 0;
    }

    auto Actors = *(((TArray<AActor *> * (*)(uintptr_t))(UE4 +
                                                         GetActorArray_offset))(
        reinterpret_cast<uintptr_t>(GWorld->PersistentLevel)));

    if (localPlayer)
    {
        for (int i = 0; i < Actors.Num(); i++)
        {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {
                auto Player = (ASTExtraPlayerCharacter *)Actor;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (config_t::esp::visual::bIgnoreAI)
                {
                    if (IsBot(Player))
                        continue;
                }

                if (config_t::aim::bIgnoreKnocked)
                {
                    if (Player->Health == 0.0f)
                        continue;
                }

                float dist = localPlayer->GetDistanceTo(Player) / 100.0f;
                if (dist > config_t::aim::DisAim)
                    continue;

                bool bVisible = true;
                if (config_t::aim::bVisCheck)
                {
                    bool bSkip = true;
                    if (LocalController->LineOfSightTo(Player, {0, 0, 0}, true))
                    {
                        bSkip = false;
                    }
                    bVisible = !bSkip;
                }

                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});

                FVector2D RootSc, HeadSc;

                if (bVisible)
                {
                    if (config_t::aim::aim_by == EAim::DISTANCE)
                    {

                        float distance = g_localPlayer->GetDistanceTo(Actor);
                        ;

                        if (distance < max)
                        {
                            max = distance;
                            Target = Player;
                        }
                    }
                    else if (config_t::aim::aim_by == EAim::CROSS_HAIR)
                    {

                        if (W2S(Root, &RootSc) && W2S(Head, &HeadSc))
                        {
                            float height = abs(HeadSc.Y - RootSc.Y);
                            float width = height * 0.65f;

                            FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};

                            FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                            FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                            float distance = FVector2D::Distance(v2Middle, v2Loc);

                            if (isInsideFOV((int)middlePoint.X, (int)middlePoint.Y))
                            {
                                if (distance < max)
                                {
                                    max = distance;
                                    Target = Player;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return Target;
}

UGameplayStatics *GetGameplayStatics()
{
    return (UGameplayStatics *)UGameplayStatics::StaticClass();
}

FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName)
{
    return Actor->GetBonePos(BoneName, FVector());
}

float GetD3DDistance(FVector a, FVector b)
{
    FVector vector = {a.X - b.X, a.Y - b.Y, a.Z - b.Z};
    return sqrt(((vector.X * vector.X) + (vector.Y * vector.Y)) + (vector.Z * vector.Z));
}

FVector GetNearest(ASTExtraPlayerCharacter *Player)
{
    FVector HeadPos = Player->GetBonePos("Head", {});
    FVector RootPos = Player->GetBonePos("Root", {});
    FVector upper_l = Player->GetBonePos("upperarm_l", {});
    FVector lowerarm_l = Player->GetBonePos("lowerarm_l", {});
    FVector hand_l = Player->GetBonePos("hand_l", {});
    FVector thigh_l = Player->GetBonePos("thigh_l", {});
    FVector calf_l = Player->GetBonePos("calf_l", {});
    FVector foot_l = Player->GetBonePos("foot_l", {});
    FVector neck_01 = Player->GetBonePos("neck_01", {});
    FVector pelvis = Player->GetBonePos("pelvis", {});

    FVector2D HeadPosSC;
    FVector2D upper_lPoSC;
    FVector2D lowerarm_lSC;
    FVector2D hand_lSC;
    FVector2D thigh_lSC;
    FVector2D calf_lSC;
    FVector2D foot_lSC;

    FVector2D neck_01SC;
    FVector2D pelvisSC;
    FVector2D RootPosSC;
    float FloatBorder = 1.f;
    if (
        W2S(HeadPos, (FVector2D *)&HeadPosSC) &&
        W2S(upper_l, (FVector2D *)&upper_lPoSC) &&
        W2S(lowerarm_l, (FVector2D *)&lowerarm_lSC) &&
        W2S(hand_l, (FVector2D *)&hand_lSC) &&
        W2S(thigh_l, (FVector2D *)&thigh_lSC) &&
        W2S(calf_l, (FVector2D *)&calf_lSC) &&
        W2S(foot_l, (FVector2D *)&foot_lSC) &&
        W2S(neck_01, (FVector2D *)&neck_01SC) &&
        W2S(pelvis, (FVector2D *)&pelvisSC) &&
        W2S(RootPos, (FVector2D *)&RootPosSC))
    {
        while (true)
        {
            if (FloatBorder > config_t::aim::fovSize)
                break;
            if (isInsideFOVNearest((int)HeadPosSC.X, (int)HeadPosSC.Y, FloatBorder))
            {
                return HeadPos;
            }
            if (isInsideFOVNearest((int)upper_lPoSC.X, (int)upper_lPoSC.Y, FloatBorder))
            {
                return upper_l;
            }
            if (isInsideFOVNearest((int)lowerarm_lSC.X, (int)lowerarm_lSC.Y, FloatBorder))
            {
                return lowerarm_l;
            }
            if (isInsideFOVNearest((int)hand_lSC.X, (int)hand_lSC.Y, FloatBorder))
            {
                return HeadPos;
            }
            if (isInsideFOVNearest((int)thigh_lSC.X, (int)thigh_lSC.Y, FloatBorder))
            {
                return thigh_l;
            }
            if (isInsideFOVNearest((int)calf_lSC.X, (int)calf_lSC.Y, FloatBorder))
            {
                return calf_l;
            }
            if (isInsideFOVNearest((int)foot_lSC.X, (int)foot_lSC.Y, FloatBorder))
            {
                return foot_l;
            }
            if (isInsideFOVNearest((int)neck_01SC.X, (int)neck_01SC.Y, FloatBorder))
            {
                return neck_01;
            }
            if (isInsideFOVNearest((int)pelvisSC.X, (int)pelvisSC.Y, FloatBorder))
            {
                return pelvis;
            }
            if (isInsideFOVNearest((int)RootPosSC.X, (int)RootPosSC.Y, FloatBorder))
            {
                return RootPos;
            }
            FloatBorder += 1.f;
        }
    }
    return HeadPos;
}

FVector Subtract_VectorVector(const FVector &A, const FVector &B)
{
    FVector Result;
    Result.X = A.X - B.X;
    Result.Y = A.Y - B.Y;
    Result.Z = A.Z - B.Z;
    return Result;
}

FRotator Conv_VectorToRotator(const FVector &InVec)
{
    FRotator Result;

    Result.Yaw = atan2(InVec.Y, InVec.X) * 180.f / (float)3.14159265358979323846;

    Result.Pitch = atan2(InVec.Z, sqrt(InVec.X * InVec.X + InVec.Y * InVec.Y)) * 180.f / (float)3.14159265358979323846;

    Result.Roll = 0;

    return Result;
}

FVector Multiply_VectorFloat(const FVector &A, float B)
{
    FVector Result;
    Result.X = A.X * B;
    Result.Y = A.Y * B;
    Result.Z = A.Z * B;
    return Result;
}

FVector Add_VectorVector(const FVector &A, const FVector &B)
{
    FVector Result;
    Result.X = A.X + B.X;
    Result.Y = A.Y + B.Y;
    Result.Z = A.Z + B.Z;
    return Result;
}

void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2) = 0;
void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1)
{

    if (config_t::aim::enabled && config_t::aim::aim_type == EType::BULLET)
    {
        ASTExtraPlayerCharacter *Target = GetBestLineTarget();
        if (Target)
        {
            bool triggerOk = false;
            if (config_t::aim::type_trigger != EAimTrigger::NONE)
            {
                if (config_t::aim::type_trigger == EAimTrigger::SHOOTING)
                {
                    triggerOk = g_localPlayer->bIsWeaponFiring;
                }
                else if (config_t::aim::type_trigger == EAimTrigger::SCOPING)
                {
                    triggerOk = g_localPlayer->bIsGunADS;
                }
                else if (config_t::aim::type_trigger == EAimTrigger::BOTH)
                {
                    triggerOk = g_localPlayer->bIsWeaponFiring && g_localPlayer->bIsGunADS;
                }
                else if (config_t::aim::type_trigger == EAimTrigger::ANY)
                {
                    triggerOk = g_localPlayer->bIsWeaponFiring || g_localPlayer->bIsGunADS;
                }
            }
            else
                triggerOk = true;
            if (triggerOk)
            {
                FVector targetAimPos = Target->GetBonePos("Head", {});
                if (config_t::aim::type_target == EAimTarget::CHEST)
                {
                    targetAimPos.Z -= 25.0f;
                }
                if (config_t::aim::type_target == EAimTarget::BODY)
                {
                    targetAimPos.Z -= 50.0f;
                }

                if (config_t::aim::type_target == EAimTarget::NEAREST)
                {
                    targetAimPos = GetNearest(Target);
                }

                UShootWeaponEntity *ShootWeaponEntityComponent = thiz->ShootWeaponEntityComponent;

                if (ShootWeaponEntityComponent)
                {
                    ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                    if (CurrentVehicle)
                    {
                        FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                        float dist = g_localPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;

                        targetAimPos = Add_VectorVector(targetAimPos, Multiply_VectorFloat(LinearVelocity, timeToTravel));
                    }
                    else
                    {
                        FVector Velocity = Target->GetVelocity();
                        float dist = g_localPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;
                        targetAimPos = Add_VectorVector(targetAimPos, Multiply_VectorFloat(Velocity, timeToTravel));
                    }

                    FVector fDir = Subtract_VectorVector(targetAimPos, g_LocalController->PlayerCameraManager->CameraCache.POV.Location);
                    rot = Conv_VectorToRotator(fDir);
                }
            }
        }
    }
    return orig_shoot_event(thiz, start, rot, weapon, unk1);
}



void DrawRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, float Thickness, FLinearColor Color)
{
    HUD->DrawLine(Pos.X, Pos.Y, Pos.X + Width, Pos.Y, Color, Thickness);
    HUD->DrawLine(Pos.X, Pos.Y, Pos.X, Pos.Y + Height, Color, Thickness);
    HUD->DrawLine(Pos.X + Width, Pos.Y, Pos.X + Width, Pos.Y + Height, Color, Thickness);
    HUD->DrawLine(Pos.X, Pos.Y + Height, Pos.X + Width, Pos.Y + Height, Color, Thickness);
}

void DrawFilledRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, FLinearColor Color)
{
    HUD->DrawRect(Color, Pos.X, Pos.Y, Width, Height);
}

void DrawLine(AHUD *HUD, FVector2D posFrom, FVector2D posTo, float Thickness, FLinearColor Color)
{
    HUD->DrawLine(posFrom.X, posFrom.Y, posTo.X, posTo.Y, Color, Thickness);
}

#define TSL_FONT_DEFAULT_SIZE 20
static UFont *tslFont = 0, *robotoTinyFont = 0;

void DrawOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false)
{
    UCanvas *Canvas = HUD->Canvas;
    Canvas->K2_DrawText(tslFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, true, OutlineColor);
}

void DrawText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, bool isCenter = false)
{
    UCanvas *Canvas = HUD->Canvas;
    Canvas->K2_DrawText(tslFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, false, {});
}

void DrawSmallOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false)
{
    UCanvas *Canvas = HUD->Canvas;
    Canvas->K2_DrawText(robotoTinyFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, true, OutlineColor);
}

void DrawSmallText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, bool isCenter = false)
{
    UCanvas *Canvas = HUD->Canvas;
    Canvas->K2_DrawText(robotoTinyFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, false, {});
}

void DrawArrows(AHUD *HUD, FVector2D xy1, FVector2D xy2, FVector2D xy3, FVector2D xy4, FVector2D xy5, FVector2D xy6, FVector2D xy7, float thickness, FLinearColor color)
{
    DrawLine(HUD, xy1, xy2, thickness, color);
    DrawLine(HUD, xy2, xy3, thickness, color);
    DrawLine(HUD, xy3, xy7, thickness, color);
    DrawLine(HUD, xy7, xy6, thickness, color);
    DrawLine(HUD, xy6, xy5, thickness, color);
    DrawLine(HUD, xy5, xy4, thickness, color);
    DrawLine(HUD, xy4, xy1, thickness, color);
}

void Line(AHUD *HUD, FVector2D origin, FVector2D dest, FLinearColor Color)
{
    HUD->DrawLine(origin.X, origin.Y, dest.X, dest.Y, Color, 2.0f);
}

void Box3D(AHUD *HUD, FVector origin, FVector extends, FLinearColor Color)
{
    origin.X -= extends.X / 2.f;
    origin.Y -= extends.Y / 2.f;
    origin.Z -= extends.Z / 2.f;

    FVector one = origin;
    FVector two = origin;
    two.X += extends.X;
    FVector tree = origin;
    tree.X += extends.X;
    tree.Y += extends.Y;
    FVector four = origin;
    four.Y += extends.Y;

    FVector five = one;
    five.Z += extends.Z;
    FVector six = two;
    six.Z += extends.Z;
    FVector seven = tree;
    seven.Z += extends.Z;
    FVector eight = four;
    eight.Z += extends.Z;

    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
        W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8))
    {

        Line(HUD, s1, s2, Color);
        Line(HUD, s2, s3, Color);
        Line(HUD, s3, s4, Color);
        Line(HUD, s4, s1, Color);

        Line(HUD, s5, s6, Color);
        Line(HUD, s6, s7, Color);
        Line(HUD, s7, s8, Color);
        Line(HUD, s8, s5, Color);

        Line(HUD, s1, s5, Color);
        Line(HUD, s2, s6, Color);
        Line(HUD, s3, s7, Color);
        Line(HUD, s4, s8, Color);
    }
}



void DrawCircle(AHUD *HUD, int x, int y, int radius, int numsides, FLinearColor OutlineColor)
{
    UCanvas *Canvas = HUD->Canvas;
    float Step = M_PI * 2.0 / numsides;
    int Count = 0;
    FVector2D V[128];
    for (float a = 0; a < M_PI * 2.0; a += Step)
    {
        float X1 = radius * cos(a) + x;
        float Y1 = radius * sin(a) + y;
        float X2 = radius * cos(a + Step) + x;
        float Y2 = radius * sin(a + Step) + y;
        V[Count].X = X1;
        V[Count].Y = Y1;
        V[Count + 1].X = X2;
        V[Count + 1].Y = Y2;
        Canvas->K2_DrawLine(FVector2D({V[Count].X, V[Count].Y}), FVector2D({X2, Y2}), 1.f, OutlineColor);
    }
}

static std::string ss1;
static std::string ss2;
static std::string ss3;
static std::string ss4;
static std::string ss5;
static std::string ss6;
static std::string ss7;
static std::string ss8;
static std::string ss9;
static std::string ss10;
static std::string ss11;
static std::string ss12;
static std::string ss13;
static std::string ss14;
static std::string ss15 = (("MT MOD"));

void *LoadFont(void *)
{
    while (!tslFont || !robotoTinyFont)
    {
        tslFont = UObject::FindObject<UFont>("Font TSLFont.TSLFont");
        robotoTinyFont = UObject::FindObject<UFont>("Font AgencyFB_Bold.AgencyFB_Bold");
        sleep(1);
    }
    return 0;
}

void DrawLineCanvas(SDK::UCanvas *Canvas, FVector2D posFrom, FVector2D posTo, FLinearColor Color, float Thickness)
{
    Canvas->K2_DrawLine({posFrom.X, posFrom.Y}, {posTo.X, posTo.Y}, Thickness, Color);
}

static std::vector<std::string> right_arm{"neck_01", "clavicle_r",
                                          "upperarm_r", "lowerarm_r",
                                          "hand_r", "item_r"};
static std::vector<std::string> left_arm{"neck_01", "clavicle_l",
                                         "upperarm_l", "lowerarm_l", "hand_l",
                                         "item_l"};
static std::vector<std::string> spine{"Head", "neck_01", "spine_03",
                                      "spine_02", "spine_01", "pelvis"};
static std::vector<std::string> lower_right{"pelvis", "thigh_r", "calf_r",
                                            "foot_r"};
static std::vector<std::string> lower_left{"pelvis", "thigh_l", "calf_l",
                                           "foot_l"};
static std::vector<std::vector<std::string>> skeleton{right_arm, left_arm, spine,
                                                      lower_right, lower_left};

FVector W2SB(ASTExtraPlayerController *localController, FVector v)
{
    FVector out = {0, 0, 1};
    FVector2D _2d = {0, 0};
    GetGameplayStatics()->ProjectWorldToScreen(
        localController, v, false,
        &_2d);
    out.X = _2d.X;
    out.Y = _2d.Y;
    return out;
}

bool realVisible(ASTExtraPlayerController *localController, ASTExtraPlayerCharacter *m_player, FVector HeadPos)
{
    FHitResult hit{0};
    auto actorsToIgnore = TArray<AActor *>();
    return !SDK::UKismetSystemLibrary::LineTraceSingle(
        GetWorld(),
        localController->PlayerCameraManager->CameraCache.POV.Location,
        HeadPos,
        ETraceTypeQuery::TraceTypeQuery1,
        true,
        actorsToIgnore,
        EDrawDebugTrace::EDrawDebugTrace__None,
        0.0f,
        true,
        FLinearColor(),
        FLinearColor(),
        &hit);
}

void DrawRectangle3(UCanvas *Canvas, FVector2D Pos, float Width, float Height, float Thickness, FLinearColor Color)
{

    float HalfThickness = Thickness / 2.0f;
    Canvas->K2_DrawLine(FVector2D(Pos.X, Pos.Y), FVector2D(Pos.X, Pos.Y + Height), Thickness, Color);
    Canvas->K2_DrawLine(FVector2D(Pos.X, Pos.Y), FVector2D(Pos.X + Width, Pos.Y), Thickness, Color);
    Canvas->K2_DrawLine(FVector2D(Pos.X + Width, Pos.Y), FVector2D(Pos.X + Width, Pos.Y + Height), Thickness, Color);
    Canvas->K2_DrawLine(FVector2D(Pos.X, Pos.Y + Height), FVector2D(Pos.X + Width, Pos.Y + Height), Thickness, Color);
}

void DrawLine(UCanvas *Canvas, FVector2D from, FVector2D to, float thickness, FLinearColor color)
{
    Canvas->K2_DrawLine(from, to, thickness, color);
}

struct FLinearColor visCol;

bool loadFont = false;

void RenderESP(UCanvas *Canvas, int ScreenWidth, int ScreenHeight)
{

    auto GWorld = GetWorld();
    if (GWorld)
    {
        if (GWorld->PersistentLevel)
        {
            auto Actors = *(((TArray<AActor *> * (*)(uintptr_t))(UE4 + GetActorArray_offset))(reinterpret_cast<uintptr_t>(GWorld->PersistentLevel)));

            int totalEnemies = 0, totalBots = 0;

            ScreenWidth;
            ScreenHeight;

            ASTExtraPlayerCharacter *localPlayer = 0;
            ASTExtraPlayerController *localController = 0;
            if (Canvas)
            {
                static bool loadFont = false;
                if (!loadFont)
                {
                    pthread_t t;
                    pthread_create(&t, 0, LoadFont, 0);
                    loadFont = true;
                }

                if (!tslFont || !robotoTinyFont)
                    return;
                tslFont->LegacyFontSize = 20;
                tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;

                auto GWorld = GetWorld();
                std::vector<AActor *> Actors;
    {
        std::lock_guard<std::mutex> lock(actors_mutex);
        Actors = NecessaryActors;
    }

                // Kiểm tra tính hợp lệ của GWorld và các đối tượng liên quan
                if (GWorld && GWorld->PersistentLevel && GWorld->NetDriver && GWorld->NetDriver->ServerConnection)
                {
                    auto NetDriver = GWorld->NetDriver;
                    auto ServerConnection = NetDriver->ServerConnection;
                    if (ServerConnection)
                    {
                        localController = (ASTExtraPlayerController *)ServerConnection->PlayerController;
                    }
                }

                // Kiểm tra lại tính hợp lệ của localController
                if (localController)
                {
                    for (int i = 0; i < Actors.size(); i++)
                    {
                        auto Actor = Actors[i];

                        // Kiểm tra tính hợp lệ của Actor (đảm bảo không phải nullptr)
                        if (!Actor)
                            continue;

                        // Kiểm tra xem Actor có phải là ASTExtraPlayerCharacter không
                        if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
                        {
                            // So sánh PlayerKey để xác định localPlayer
                            if (((ASTExtraPlayerCharacter *)Actor)->PlayerKey == localController->PlayerKey)
                            {
                                localPlayer = (ASTExtraPlayerCharacter *)Actor;
                                break;
                            }
                        }
                    }

  

                

                    if (localPlayer)
                    {

                        if (localPlayer && localPlayer->WeaponManagerComponent && localPlayer->WeaponManagerComponent->CurrentWeaponReplicated)
                        {

                            auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)localPlayer->WeaponManagerComponent->CurrentWeaponReplicated;
                            Current_Weapon = CurrentWeaponReplicated->GetWeaponID();
                            Last_Gun_Used_To_Kill = GetWeap(Current_Weapon);
                        }

                        auto state = GWorld->GameState;

                        if (state)
                        {
                            auto OffWorkCR = (ASTExtraGameStateBase *)state;
                            ss1 = std::to_string((int)OffWorkCR->AlivePlayerNum);
                            ss2 = std::to_string((int)OffWorkCR->PlayerNum);
                            ss3 = std::to_string((int)OffWorkCR->AliveTeamNum);
                            ss4 = std::to_string((int)OffWorkCR->ElapsedTime);
                            ss5 = std::to_string((int)OffWorkCR->ElapsedTime / 60);
                        }
                        int kill_message_event_idx = 1000;
                        auto VTable = (void **)localController->VTable;
                        auto f_mprotect = [](uintptr_t addr, size_t len, int32_t prot) -> int32_t
                        {
                            static_assert(PAGE_SIZE == 4096);
                            constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
                            void *start = reinterpret_cast<void *>(addr & -page_size);
                            uintptr_t end = (addr + len + page_size - 1) & -page_size;
                            return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
                        };

                        if (VTable && (VTable[kill_message_event_idx] != kill_message_event))
                        {
                            static bool kill_msg_hooked = false;
                            if (!kill_msg_hooked) {
                                orig_kill_message_event = decltype(orig_kill_message_event)(VTable[kill_message_event_idx]);
                                f_mprotect((uintptr_t)(&VTable[kill_message_event_idx]), sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                VTable[kill_message_event_idx] = (void *)kill_message_event;
                                f_mprotect((uintptr_t)(&VTable[kill_message_event_idx]), sizeof(uintptr_t), PROT_READ | PROT_EXEC);
                                kill_msg_hooked = true;
                            }
                        }

      if (skin.bEnable)
                        {
                            if (skin.bVehicleSkin && localPlayer->CurrentVehicle && localPlayer->CurrentVehicle->VehicleAvatar)
                            {
                                if (!lastVehicle || lastVehicle != localPlayer->CurrentVehicle)
                                {
                                    int ava = localPlayer->CurrentVehicle->VehicleAvatar->GetDefaultAvatarID();
                                    int neww = GetVehSkinModded(ava);
                                    if (neww > 0)
                                    {
                                        localPlayer->CurrentVehicle->VehicleAvatar->ChangeItemAvatar(neww, false);
                                    }

                                    lastVehicle = localPlayer->CurrentVehicle;
                                }
                            }

                            else
                            {
                                lastVehicle = 0;
                            }

                            if (skin.bDeadbox)
                            {
                                auto db_array = GetAllActors1<APlayerTombBox>(GWorld);
                                for (int i = 0; i < db_array.Num(); i++)
                                {
                                    auto TombBoxx = (APlayerTombBox *)db_array[i];
                                    if (TombBoxx && TombBoxx->DamageCauser && TombBoxx->TargetPlayer) // Check pointers before dereferencing
                                    {
                                        if (TombBoxx->DamageCauser->PlayerKey == localController->PlayerKey)
                                        {
                                            auto PlayerKey = TombBoxx->TargetPlayer->PlayerKey;
                                            if (AlreadyChangedSet.find(PlayerKey) == AlreadyChangedSet.end())
                                            {
                                                auto DeadBoxAvatarCompPtr = (uintptr_t *)((uintptr_t)TombBoxx + 0x718); // DeadBoxAvatarComponent_BP_C* DeadBoxAvatarComponent_BP
                                                if (DeadBoxAvatarCompPtr)
                                                {
                                                    auto DeadBoxAvatarComp = *DeadBoxAvatarCompPtr;
                                                    if (Last_Gun_Used_To_Kill > 0)
                                                    {
                                                        ChangeItemAVc(DeadBoxAvatarComp, Last_Gun_Used_To_Kill);
                                                        AlreadyChangedSet.insert(PlayerKey);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (config_t::aim::enabled && config_t::aim::aim_type == EType::BOT)
                        {
                            ASTExtraPlayerCharacter *Target = GetBestLineTarget();
                            if (Target)
                            {
                                bool triggerOk = false;
                                if (config_t::aim::type_trigger != EAimTrigger::NONE)
                                {
                                    if (config_t::aim::type_trigger == EAimTrigger::SHOOTING)
                                    {
                                        triggerOk = g_localPlayer->bIsWeaponFiring;
                                    }
                                    else if (config_t::aim::type_trigger == EAimTrigger::SCOPING)
                                    {
                                        triggerOk = g_localPlayer->bIsGunADS;
                                    }
                                    else if (config_t::aim::type_trigger == EAimTrigger::BOTH)
                                    {
                                        triggerOk = g_localPlayer->bIsWeaponFiring && g_localPlayer->bIsGunADS;
                                    }
                                    else if (config_t::aim::type_trigger == EAimTrigger::ANY)
                                    {
                                        triggerOk = g_localPlayer->bIsWeaponFiring || g_localPlayer->bIsGunADS;
                                    }
                                }
                                else
                                    triggerOk = true;
                                if (triggerOk)
                                {
                                    FVector targetAimPos = Target->GetBonePos("Head", {});
                                    if (config_t::aim::type_target == EAimTarget::CHEST)
                                    {
                                        targetAimPos.Z -= 25.0f;
                                    }
                                    if (config_t::aim::type_target == EAimTarget::BODY)
                                    {
                                        targetAimPos.Z -= 50.0f;
                                    }
                                    auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                                    if (WeaponManagerComponent)
                                    {
                                        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                        if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                                        {
                                            auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
                                            if (CurrentWeaponReplicated)
                                            {
                                                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                                if (ShootWeaponComponent)
                                                {
                                                    UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                                    if (ShootWeaponEntityComponent)
                                                    {
                                                        if (!config_t::aim::protection)
                                                        {
                                                            ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                                                            if (CurrentVehicle)
                                                            {
                                                                FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
                                                                float dist = localPlayer->GetDistanceTo(Target);
                                                                auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;
                                                                targetAimPos = Add_VectorVector(targetAimPos, Multiply_VectorFloat(LinearVelocity, timeToTravel));
                                                                targetAimPos.Z += LinearVelocity.Z * timeToTravel + 0.5 * float(config_t::aim::protection_value) * timeToTravel * timeToTravel; // Protection
                                                            }
                                                            else
                                                            {
                                                                FVector Velocity = Target->GetVelocity();
                                                                float dist = localPlayer->GetDistanceTo(Target);
                                                                auto timeToTravel = dist / ShootWeaponEntityComponent->BulletRange;
                                                                targetAimPos = Add_VectorVector(targetAimPos, Multiply_VectorFloat(Velocity, timeToTravel));
                                                                targetAimPos.Z += Velocity.Z * timeToTravel + 0.5 * float(config_t::aim::protection_value) * timeToTravel * timeToTravel; // Protection
                                                            }
                                                        }
                                                        if (!config_t::aim::recoil_comparison)
                                                        {
                                                            if (g_localPlayer->bIsGunADS)
                                                            {
                                                                if (g_localPlayer->bIsWeaponFiring)
                                                                {
                                                                    float dist = g_localPlayer->GetDistanceTo(Target) / 100.0f;
                                                                    targetAimPos.Z -= dist * float(config_t::aim::recoil_comparison_value);
                                                                }
                                                            }
                                                        }

                                                        FVector fDir = Subtract_VectorVector(targetAimPos, localController->PlayerCameraManager->CameraCache.POV.Location);
                                                        auto Rott = Conv_VectorToRotator(fDir);
                                                        FRotator m_Rotation = localController->ControlRotation;
                                                        Rott.Pitch -= m_Rotation.Pitch;
                                                        Rott.Yaw -= m_Rotation.Yaw;
                                                        ClampAngles(Rott);
                                                        m_Rotation.Pitch += Rott.Pitch / config_t::aim::smoothness;
                                                        m_Rotation.Yaw += Rott.Yaw / config_t::aim::smoothness;
                                                        localController->SetControlRotation(m_Rotation, "");

                                                        // localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
     } 
  }
  
/*  void (*orig_Mt_Mod)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *weapon, int unk1) = 0;

void Mt_Mod(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1) {
if (config_t::aim::Magicv1) {
ASTExtraPlayerCharacter *Target = BULLET_HD();
if (Target) {
FVector targetAimPos = Target->GetBonePos("Head", {});
targetAimPos.Z -= (float) -19.0f;
FRotator sex = ToRotator(start, targetAimPos);
return orig_Mt_Mod(thiz, targetAimPos, sex, weapon, unk1);
}}
return orig_Mt_Mod(thiz, start, rot, weapon, unk1);
}*/

void *(*oPostRender)(UGameViewportClient *GameViewport, UCanvas *Canvas);
void *hPostRender(UGameViewportClient *GameViewport, UCanvas *Canvas)
{
    RenderESP(Canvas, Canvas->SizeX, Canvas->SizeY);
    return oPostRender(GameViewport, Canvas);
}
ImFont *DefaultFontCfg;
static const ImColor _randombush[] = {
    ImColor(255, 255, 255, 255),
    ImColor(255, 165, 0),
    ImColor(250, 218, 255, 255),
    ImColor(255, 255, 0, 255),
    ImColor(0, 255, 255, 255),
    ImColor(255, 150, 150, 255),
    ImColor(160, 160, 232, 255)};

bool IsAimTriggered()
{
    if (!g_localPlayer)
        return false;
    bool triggerOk = false;
    if (config_t::aim::type_trigger != EAimTrigger::NONE)
    {
        if (config_t::aim::type_trigger == EAimTrigger::SHOOTING)
        {
            triggerOk = g_localPlayer->bIsWeaponFiring;
        }
        else if (config_t::aim::type_trigger == EAimTrigger::SCOPING)
        {
            triggerOk = g_localPlayer->bIsGunADS;
        }
        else if (config_t::aim::type_trigger == EAimTrigger::BOTH)
        {
            triggerOk = g_localPlayer->bIsWeaponFiring && g_localPlayer->bIsGunADS;
        }
        else if (config_t::aim::type_trigger == EAimTrigger::ANY)
        {
            triggerOk = g_localPlayer->bIsWeaponFiring || g_localPlayer->bIsGunADS;
        }
    }
    else
        triggerOk = true;
    return triggerOk;
}

std::string GetWeaponName(int EnemyWeapon)
{
    std::string s = "";
    if (EnemyWeapon == 101001)
    {
        s += "AKM";
    }
    else if (EnemyWeapon == 101002)
    {
        s += "M16A4";
    }
    else if (EnemyWeapon == 101003)
    {
        s += "Scar-L";
    }
    else if (EnemyWeapon == 101004)
    {
        s += "M416";
    }
    else if (EnemyWeapon == 101005)
    {
        s += "Groza";
    }
    else if (EnemyWeapon == 101006)
    {
        s += "AUG";
    }
    else if (EnemyWeapon == 101007)
    {
        s += "QBZ";
    }
    else if (EnemyWeapon == 101008)
    {
        s += "M762";
    }
    else if (EnemyWeapon == 101009)
    {
        s += "Mk-47";
    }
    else if (EnemyWeapon == 101010)
    {
        s += "G36C";
    }
    else if (EnemyWeapon == 101100)
    {
        s += "Famas";
    }
    else if (EnemyWeapon == 102001)
    {
        s += "Uzi";
    }
    else if (EnemyWeapon == 102002)
    {
        s += "UMP-45";
    }
    else if (EnemyWeapon == 102003)
    {
        s += "Vector";
    }
    else if (EnemyWeapon == 102004)
    {
        s += "Thompson";
    }
    else if (EnemyWeapon == 102005)
    {
        s += "Bizon";
    }
    else if (EnemyWeapon == 103001)
    {
        s += "Kar98";
    }
    else if (EnemyWeapon == 103002)
    {
        s += "M24";
    }
    else if (EnemyWeapon == 103003)
    {
        s += "AWM";
    }
    else if (EnemyWeapon == 103011)
    {
        s += "Mosin Nagant";
    }
    else if (EnemyWeapon == 103012)
    {
        s += "AMR";
    }
    else if (EnemyWeapon == 103004)
    {
        s += "SKS";
    }
    else if (EnemyWeapon == 103005)
    {
        s += "VSS";
    }
    else if (EnemyWeapon == 103006)
    {
        s += "Mini-14";
    }
    else if (EnemyWeapon == 103007)
    {
        s += "MK14";
    }
    else if (EnemyWeapon == 103008)
    {
        s += "Win-94";
    }
    else if (EnemyWeapon == 103009)
    {
        s += "SLR";
    }
    else if (EnemyWeapon == 103010)
    {
        s += "QBU";
    }
    else if (EnemyWeapon == 103100)
    {
        s += "MK12";
    }
    else if (EnemyWeapon == 104001)
    {
        s += "S686";
    }
    else if (EnemyWeapon == 104002)
    {
        s += "S1897";
    }
    else if (EnemyWeapon == 104003)
    {
        s += "S12K";
    }
    else if (EnemyWeapon == 104004)
    {
        s += "DPS";
    }
    else if (EnemyWeapon == 104101)
    {
        s += "M1014";
    }
    else if (EnemyWeapon == 106006)
    {
        s += "Sawed-Off";
    }
    else if (EnemyWeapon == 106001)
    {
        s += "P92";
    }
    else if (EnemyWeapon == 106002)
    {
        s += "P1911";
    }
    else if (EnemyWeapon == 106003)
    {
        s += "R1895";
    }
    else if (EnemyWeapon == 106004)
    {
        s += "P18C";
    }
    else if (EnemyWeapon == 106005)
    {
        s += "R45";
    }
    else if (EnemyWeapon == 106008)
    {
        s += "Vz61";
    }
    else if (EnemyWeapon == 106010)
    {
        s += "Desert Eagle";
    }
    else if (EnemyWeapon == 107001)
    {
        s += "Nỏ Thần";
    }
    else if (EnemyWeapon == 602001)
    {
        s += "Bom Choáng";
    }
    else if (EnemyWeapon == 602002)
    {
        s += "Bom Khói";
    }
    else if (EnemyWeapon == 602003)
    {
        s += "Bom Lửa";
    }
    else if (EnemyWeapon == 602004)
    {
        s += "Lựu Đạn";
    }
    else if (EnemyWeapon == 108001)
    {
        s += "Mã Tấu";
    }
    else if (EnemyWeapon == 108002)
    {
        s += "Xà Beng";
    }
    else if (EnemyWeapon == 108003)
    {
        s += "Liem";
    }
    else if (EnemyWeapon == 105001)
    {
        s += "M249";
    }
    else if (EnemyWeapon == 105002)
    {
        s += "DP-28";
    }
    else
    {
        s = std::to_string(EnemyWeapon);
    }
    return s;
}


void Circle3D(ImDrawList *draw, FVector origin, float radius, ImColor color, float thinkless)
{
    const int doan_thang = 50;
    float step = 2 * IM_PI / doan_thang;
    FVector2D prev;
    Vector3 curValid3 = Vector3(origin.X + radius, origin.Y, origin.Z);
    FVector curValidF;
    curValidF.X = curValid3.X;
    curValidF.Y = curValid3.Y;
    curValidF.Z = curValid3.Z;
    bool curValid = W2S(curValidF, &prev);

    for (int i = 1; i <= doan_thang; ++i)
    {
        float angle = i * step;
        FVector2D cur;
        Vector3 nextValid3 = Vector3(origin.X + radius * cos(angle), origin.Y + radius * sin(angle), origin.Z);
        FVector nextValidF;
        nextValidF.X = nextValid3.X;
        nextValidF.Y = nextValid3.Y;
        nextValidF.Z = nextValid3.Z;
        bool nextValid = W2S(nextValidF, &cur);
        if (curValid && nextValid)
        {
            draw->AddLine(ImVec2(prev.X, prev.Y), ImVec2(cur.X, cur.Y), color, thinkless);
        }
        curValid = nextValid;
        prev = cur;
    }
}


bool isEqual(string s1, const char *check)
{
    string s2(check);
    return (s1 == s2);
}

struct VECTOR3
{
    float X;
    float Y;
    float Z;
};
struct Matrix
{
    float m[4][4];
};

Matrix GetMatrix()
{
    static UCanvas *Canvas = nullptr;

    if (Canvas == nullptr)
    {
        Canvas = UObject::FindObject<UCanvas>("Canvas Transient.DebugCanvasObject");
    }

    if (!Canvas)
    {
        return Matrix{};
    }

    uintptr_t lodalele;

#if defined(__LP64__)
    lodalele = 0x270;
#else
    lodalele = 0x200;
#endif

    return *(Matrix *)((uintptr_t)Canvas + lodalele);
}

bool WorldToScreenPlayer(FVector pos, FVector &screen, int *distance)
{
    Matrix ViewMatrix = GetMatrix();

    screen = {};
    *distance = 0;

    float screenW = (ViewMatrix.m[0][3] * pos.X) + (ViewMatrix.m[1][3] * pos.Y) + (ViewMatrix.m[2][3] * pos.Z + ViewMatrix.m[3][3]);
    if (screenW < 0.0001f)
        return false;

    *distance = (screenW / 100);
    float screenY = (ViewMatrix.m[0][1] * pos.X) + (ViewMatrix.m[1][1] * pos.Y) + (ViewMatrix.m[2][1] * (pos.Z + 85) + ViewMatrix.m[3][1]);
    float screenX = (ViewMatrix.m[0][0] * pos.X) + (ViewMatrix.m[1][0] * pos.Y) + (ViewMatrix.m[2][0] * pos.Z + ViewMatrix.m[3][0]);
    screen.Y = (glHeight / 2.f) - (glHeight / 2.f) * screenY / screenW;
    screen.X = (glWidth / 2.f) + (glWidth / 2.f) * screenX / screenW;
    float y1 = (glHeight / 2.f) - (ViewMatrix.m[0][1] * pos.X + ViewMatrix.m[1][1] * pos.Y + ViewMatrix.m[2][1] * (pos.Z - 95) + ViewMatrix.m[3][1]) * (glHeight / 2.f) / screenW;
    screen.Z = y1 - screen.Y;

    return !(screen.X == 0 && screen.Y == 0 && screen.Z == 0);
}

bool WorldToScreenBone(FVector Position, FVector2D *Screen)
{
    Matrix ViewMatrix = GetMatrix();

    float ScreenW = (ViewMatrix.m[0][3] * Position.X) + (ViewMatrix.m[1][3] * Position.Y) + (ViewMatrix.m[2][3] * Position.Z + ViewMatrix.m[3][3]);
    if (ScreenW < 0.0001f)
        return false;

    ScreenW = 1 / ScreenW;
    float SightX = (glWidth / 2);
    float SightY = (glHeight / 2);

    Screen->X = SightX + (ViewMatrix.m[0][0] * Position.X + ViewMatrix.m[1][0] * Position.Y + ViewMatrix.m[2][0] * Position.Z + ViewMatrix.m[3][0]) * ScreenW * SightX;
    Screen->Y = SightY - (ViewMatrix.m[0][1] * Position.X + ViewMatrix.m[1][1] * Position.Y + ViewMatrix.m[2][1] * Position.Z + ViewMatrix.m[3][1]) * ScreenW * SightY;

    return true;
}
struct D3DMatrix
{
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};


static void ShowState(bool* p_open)
{
    ImGuiIO& io = ImGui::GetIO();

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.6f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(15, 15, 15, 160));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    if (!ImGui::Begin("##GameInfo", p_open, flags))
    {
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);
        ImGui::End();
        return;
    }

    ImGui::SetWindowFontScale(0.95f);

    const char* title = "Game information";
    ImVec2 titleSize = ImGui::CalcTextSize(title);
    float winWidth = ImGui::GetWindowWidth();

    float centerX = winWidth * 0.5f;
    float textX = centerX - titleSize.x * 0.5f;

    ImGui::SetCursorPosX(textX);

    ImGui::TextColored(ImVec4(0.0f, 0.6f, 1.0f, 1.0f), "%s", title);


    ImDrawList* draw = ImGui::GetWindowDrawList();

    ImVec2 p_line1 = ImGui::GetCursorScreenPos();

    draw->AddLine(
        ImVec2(ImGui::GetWindowPos().x + 10, p_line1.y + 2),
        ImVec2(ImGui::GetWindowPos().x + winWidth - 10, p_line1.y + 2),
        IM_COL32(0, 153, 255, 150),
        1.0f
    );

    ImGui::Dummy(ImVec2(0, 6));


    if (g_LocalController)
    {
        ImGui::TextColored(
            ImVec4(0.94f, 0.94f, 0.94f, 1.0f),
            "%s players with %s teams, real players: %s",
            ss1.c_str(),
            ss3.c_str(),
            ss2.c_str()
        );


        ImVec2 p_line2 = ImGui::GetCursorScreenPos();

        draw->AddLine(
            ImVec2(ImGui::GetWindowPos().x + 10, p_line2.y + 4),
            ImVec2(ImGui::GetWindowPos().x + winWidth - 10, p_line2.y + 4),
            IM_COL32(0, 153, 255, 150),
            1.0f
        );

        ImGui::Dummy(ImVec2(0, 8));


        ImGui::TextColored(
            ImVec4(0.94f, 0.94f, 0.94f, 1.0f),
            "In match : %ss",
            ss4.c_str()
        );


        ImGui::SameLine(winWidth - 85);

        ImGui::TextColored(
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
            "FPS :"
        );

        ImGui::SameLine();

        ImGui::TextColored(
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
            "%.0f",
            io.Framerate
        );
    }
    else
    {
        ImGui::TextColored(
            ImVec4(0.6f, 0.6f, 0.65f, 1.0f),
            "Waiting for match..."
        );
    }


    ImGui::End();

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(2);
}

static vector<APickUpWrapperActor *> ARNearestCache = {};
static vector<APickUpWrapperActor *> ARNearestList = {};

bool AntiBan = false;
bool AdaAntiBan = false;
static inline uint64_t GetTickCountMs() {
    using namespace std::chrono;
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}

bool EnemyAiming;
static bool isBlocked      = false;
bool isLogin = true;
static uint64_t matchEnterTime = 0;
FVector WorldToRadar(float Yaw, FVector Origin, FVector LocalOrigin, float PosX, float PosY, Vector3 Size, bool &outbuff) {
bool flag = false;
double num = (double)Yaw;
double num2 = num * 0.017453292519943295;
float num3 = (float)std::cosf(num2);
float num4 = (float)std::sinf(num2);
float num5 = Origin.X - LocalOrigin.X;
float num6 = Origin.Y - LocalOrigin.Y;
FVector Xector;
Xector.X = (num6 * num3 - num5 * num4) / 150.f;
Xector.Y = (num5 * num3 + num6 * num4) / 150.f;
FVector Xector2;
Xector2.X = Xector.X + PosX + Size.X / 2.f;
Xector2.Y = -Xector.Y + PosY + Size.Y / 2.f;
bool flag2 = Xector2.X > PosX + Size.X;
if (flag2) {
Xector2.X = PosX + Size.X;
} else {
bool flag3 = Xector2.X < PosX;
if (flag3) {
Xector2.X = PosX;
}}
bool flag4 = Xector2.Y > PosY + Size.Y;
if (flag4) {
Xector2.Y = PosY + Size.Y;
} else {
bool flag5 = Xector2.Y < PosY;
if (flag5) {
Xector2.Y = PosY;
}}
bool flag6 = Xector2.Y == PosY || Xector2.X == PosX;
if (flag6) {
flag = true;
}
outbuff = flag;
return Xector2;
}
void DrawESP(ImDrawList *draw) {
    using namespace config_t::esp;
    int totalEnemies = 0, totalBots = 0;

    ASTExtraPlayerCharacter *localPlayer = nullptr;
    ASTExtraPlayerController *LocalController = nullptr;

    auto GWorld = GetWorld();
    std::vector<AActor *> Actors;
    {
        std::lock_guard<std::mutex> lock(actors_mutex);
        Actors = NecessaryActors;
    }

    if (GWorld && GWorld->PersistentLevel && GWorld->NetDriver && GWorld->NetDriver->ServerConnection)
    {
        auto NetDriver = GWorld->NetDriver;
        auto ServerConnection = NetDriver->ServerConnection;
        if (ServerConnection)
        {
            LocalController = (ASTExtraPlayerController *)ServerConnection->PlayerController;
        }
    }

    if (LocalController == nullptr) {
        matchEnterTime = 0;
        if (isBlocked) {
            NotifyBlock("THE MATCH IS OVER!");
            isBlocked = false;
        }
    } else {
        if (matchEnterTime == 0)
            matchEnterTime = GetTickCountMs();

        uint64_t elapsed = GetTickCountMs() - matchEnterTime;

        if (!isBlocked && elapsed >= 8000) {
            NotifyBlock("Blocked OK!");
            isBlocked = true;
        }
    }

    if (LocalController)
    {
        for (int i = 0; i < Actors.size(); i++)
        {
            auto Actor = Actors[i];
            if (!Actor)
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {
                if (((ASTExtraPlayerCharacter *)Actor)->PlayerKey == LocalController->PlayerKey)
                {
                    localPlayer = (ASTExtraPlayerCharacter *)Actor;
                    break;
                }
            }
        }

        if (localPlayer)
        {
            if (localPlayer->PartHitComponent)
            {
                auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++)
                {
                    ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                }
                localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }

            if (g_LocalController)
            {
                if (g_localPlayer && g_localPlayer->RootComponent)
                {
                    if (g_localPlayer->PartHitComponent)
                    {
                        auto ConfigCollisionDistSqAngles = g_localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                        for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++)
                        {
                            ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                        }
                        g_localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                    }

                    if (config_t::aim::aim_type == EType::BULLET)
                    {
                        auto WeaponManagerComponent = g_localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent)
                        {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                            {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated)
                                {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent)
                                    {
                                        int shoot_event_idx = 174;
                                        auto f_mprotect = [](uintptr_t addr, size_t len, int32_t prot) -> int32_t
                                        {
                                            static_assert(PAGE_SIZE == 4096);
                                            constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                            void *start = reinterpret_cast<void *>(addr & -page_size);
                                            uintptr_t end = (addr + len + page_size - 1) & -page_size;
                                            return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
                                        };
                                        auto VTable = (void **)ShootWeaponComponent->VTable;
                                        if (VTable && (VTable[shoot_event_idx] != shoot_event))
                                        {
                                            static bool shoot_hooked = false;
                                            if (!shoot_hooked) {
                                                orig_shoot_event = decltype(orig_shoot_event)(VTable[shoot_event_idx]);
                                                f_mprotect((uintptr_t)(&VTable[shoot_event_idx]), sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                                VTable[shoot_event_idx] = (void *)shoot_event;
                                                shoot_hooked = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (config_t::aim::enabled)
                    {
                        if (config_t::aim::aim_by == EAim::CROSS_HAIR)
                        {
                            draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), config_t::aim::fovSize, IM_COL32(180, 40, 40, 150), 0, 1.0f);
                        }

                        if (config_t::aim::bShowTarget)
                        {
                            auto Target = GetBestLineTarget();
                            if (Target)
                            {
                                auto target = Target->GetBonePos("Head", {});
                                auto foot = Target->GetBonePos("foot_r", {});
                                FVector targetSC, footSC;
                                if (W2S2(target, (FVector2D *)&targetSC) && W2S2(foot, (FVector2D *)&footSC))
                                {
                                    draw->AddLine({(float)glWidth / 2, 716}, {footSC.X, footSC.Y}, YELLOW(255), 0.5f);
                                }
                            }
                        }
                    }
                }
            }

            if (WideValues && localPlayer->ThirdPersonCameraComponent)
            {
                *(float *)((uintptr_t)&localPlayer->ThirdPersonCameraComponent->OrthoWidth - sizeof(float)) = WideValues;
            }


            for (auto &Actor : Actors)
            {
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
                {
                    auto Player = (ASTExtraPlayerCharacter *)Actor;  
                    
                    float Distance = Player->GetDistanceTo(localPlayer) / 100.0f;

                    if (Distance > 500.0f)
                        continue;

                    if (Player->PlayerKey == LocalController->PlayerKey)
                        continue;

                    if (Player->TeamID == LocalController->TeamID)
                        continue;

                    if (Player->bDead)
                        continue;
                        
                    if (config_t::esp::visual::bIgnoreAI && IsBot(Player))
                        continue;
                        
                    float HeightOfName = 0;
                    if (IsBot(Player)) totalBots++;
                    else totalEnemies++;

                    FVector PlayerPos;
                    ASTExtraVehicleBase *CurrentVehiclea = Player->CurrentVehicle;
                    if (CurrentVehiclea) {
                        PlayerPos = CurrentVehiclea->RootComponent->RelativeLocation;
                    } else {
                        PlayerPos = Player->RootComponent->RelativeLocation;
                    }

                    bool IsVisible = false;
                    if (LocalController->LineOfSightTo(Player, {0, 0, 0}, true))
                    {
                        IsVisible = true;
                    }
                    
                    unsigned int FinalAlertColor;
                    if (IsVisible)
                    {
                        FinalAlertColor = IM_COL32(0, 255, 0, 240);
                    }
                    else
                    {
                        FinalAlertColor = IM_COL32(255, 0, 0, 240);
                    }

                    if (visual::TRIANGLE) 
                    {
                        FVector MyPosition, EnemyPosition;
                        ASTExtraVehicleBase *CurrentVehicleLocal = localPlayer->CurrentVehicle;
                        if (CurrentVehicleLocal) {
                            MyPosition = CurrentVehicleLocal->RootComponent->RelativeLocation;
                        } else {
                            MyPosition = localPlayer->RootComponent->RelativeLocation;
                        }

                        EnemyPosition = PlayerPos;

                        float CameraYaw = LocalController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw;
                        float diffX = EnemyPosition.X - MyPosition.X;
                        float diffY = EnemyPosition.Y - MyPosition.Y;

                        float enemyAngleRad = atan2f(diffY, diffX);
                        float enemyAngleDeg = enemyAngleRad * (180.0f / M_PI);
                        float relativeAngleDeg = enemyAngleDeg - CameraYaw;
                        float finalRad = (relativeAngleDeg - 90.0f) * (M_PI / 180.0f);

                        float centerX = (float)glWidth / 2.0f;
                        float centerY = (float)glHeight / 2.0f;
                        float AlertRadius = 140.0f; 

                        float new_point_x = centerX + AlertRadius * cosf(finalRad);
                        float new_point_y = centerY + AlertRadius * sinf(finalRad);

                        std::array<Vector3, 3> points{
                            Vector3(new_point_x - 22.0f, new_point_y - 13.0f, 0.f),
                            Vector3(new_point_x + 22.0f, new_point_y, 0.f),
                            Vector3(new_point_x - 22.0f, new_point_y + 13.0f, 0.f)
                        };
                        
                        RotateTriangle(points, relativeAngleDeg - 90.0f);

                        draw->AddTriangle(ImVec2(points.at(0).X, points.at(0).Y), ImVec2(points.at(1).X, points.at(1).Y), ImVec2(points.at(2).X, points.at(2).Y), FinalAlertColor, 2.5f);
                        draw->AddTriangleFilled(ImVec2(points.at(0).X, points.at(0).Y), ImVec2(points.at(1).X, points.at(1).Y), ImVec2(points.at(2).X, points.at(2).Y), FinalAlertColor);
                    }
int SCOLOR,WHITE;
if (IsVisible) {
SCOLOR = IM_COL32(0,255,0,255);
}else{
SCOLOR = IM_COL32(255,0,0,255);
}
WHITE = IM_COL32(255,255,255,255);                    
if (visual::bAlert) {
bool shit = false;
FVector MyPosition = Player->CurrentVehicle ? Player->CurrentVehicle->RootComponent->RelativeLocation : Player->RootComponent->RelativeLocation;
FVector EnemyPosition = localPlayer->CurrentVehicle ? localPlayer->CurrentVehicle->RootComponent->RelativeLocation : localPlayer->RootComponent->RelativeLocation;
FVector EntityPos = WorldToRadar(LocalController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw, MyPosition, EnemyPosition, NULL, NULL, Vector3(glWidth, glHeight, 0), shit);
FVector angle = FVector();
Vector3 forward = Vector3((float)(glWidth / 2) - EntityPos.X, (float)(glHeight / 2) - EntityPos.Y, 0.0f);
VectorAnglesRadar(forward, angle);
const auto angle_yaw_rad = MRB(angle.Y + 180.f);
const auto new_point_x = (glWidth / 2) + (43 /*alert dist from me*/) / 2 * 4 * cosf(angle_yaw_rad);
const auto new_point_y = (glHeight / 2) + (43 /*alert dist from me*/) / 2 * 4 * sinf(angle_yaw_rad);
draw->AddCircle(ImVec2(new_point_x, new_point_y), 9.0f, SCOLOR, 64, 4.0f);
}



if (config_t::esp::visual::bSkeleton)
                        {
                            auto HeadPosop = Player->GetBonePos("Head", {}); HeadPosop.Z -= 5.0f; FVector HeadBoneProjected;
                            auto HeadPosop2 = Player->GetBonePos("Head", {}); HeadPosop2.Z += 7.0f; FVector HeadBoneProjected2;
                            auto RootPosB = Player->GetBonePos("Root", {}); FVector RootBoneProjected;
                            auto neck_01 = Player->GetBonePos("neck_01", {}); FVector NeckBonePrijected;
                            auto upper_r = Player->GetBonePos("upperarm_r", {}); FVector upper_rPoSC;
                            auto lowerarm_r = Player->GetBonePos("lowerarm_r", {}); FVector lowerarm_rPoSC;
                            auto hand_r = Player->GetBonePos("hand_r", {}); FVector hand_rPoSC;
                            auto upper_l = Player->GetBonePos("upperarm_l", {}); FVector upper_lPoSC;
                            auto lowerarm_l = Player->GetBonePos("lowerarm_l", {}); FVector lowerarm_lSC;
                            auto hand_l = Player->GetBonePos("hand_l", {}); FVector hand_lPoSC;
                            auto thigh_l = Player->GetBonePos("thigh_l", {}); FVector thigh_lPoSC;
                            auto calf_l = Player->GetBonePos("calf_l", {}); FVector calf_lPoSC;
                            auto foot_l = Player->GetBonePos("foot_l", {}); FVector foot_lPoSC;
                            auto thigh_r = Player->GetBonePos("thigh_r", {}); FVector thigh_rPoSC;
                            auto calf_r = Player->GetBonePos("calf_r", {}); FVector calf_rPoSC;
                            auto foot_r = Player->GetBonePos("foot_r", {}); FVector foot_rPoSC;
                            auto Pelvis = Player->GetBonePos("pelvis", {}); FVector PelvisPoSC;

                            if (WorldToScreenBone(HeadPosop, (FVector2D *)&HeadBoneProjected) &&
                                WorldToScreenBone(HeadPosop2, (FVector2D *)&HeadBoneProjected2) &&
                                WorldToScreenBone(upper_r, (FVector2D *)&upper_rPoSC) &&
                                WorldToScreenBone(upper_l, (FVector2D *)&upper_lPoSC) &&
                                WorldToScreenBone(lowerarm_r, (FVector2D *)&lowerarm_rPoSC) &&
                                WorldToScreenBone(hand_r, (FVector2D *)&hand_rPoSC) &&
                                WorldToScreenBone(lowerarm_l, (FVector2D *)&lowerarm_lSC) &&
                                WorldToScreenBone(hand_l, (FVector2D *)&hand_lPoSC) &&
                                WorldToScreenBone(thigh_l, (FVector2D *)&thigh_lPoSC) &&
                                WorldToScreenBone(calf_l, (FVector2D *)&calf_lPoSC) &&
                                WorldToScreenBone(foot_l, (FVector2D *)&foot_lPoSC) &&
                                WorldToScreenBone(thigh_r, (FVector2D *)&thigh_rPoSC) &&
                                WorldToScreenBone(calf_r, (FVector2D *)&calf_rPoSC) &&
                                WorldToScreenBone(foot_r, (FVector2D *)&foot_rPoSC) &&
                                WorldToScreenBone(neck_01, (FVector2D *)&NeckBonePrijected) &&
                                WorldToScreenBone(Pelvis, (FVector2D *)&PelvisPoSC) &&
                                WorldToScreenBone(RootPosB, (FVector2D *)&RootBoneProjected))
                            {
                                float BoneThick = 2.0f;
float HeadRadius = abs(HeadBoneProjected2.Y - HeadBoneProjected.Y);

draw->AddCircle({HeadBoneProjected2.X, HeadBoneProjected2.Y}, HeadRadius, SCOLOR, 0, BoneThick);

                                draw->AddLine({upper_rPoSC.X, upper_rPoSC.Y}, {NeckBonePrijected.X, NeckBonePrijected.Y}, SCOLOR, BoneThick);
                                draw->AddLine({upper_lPoSC.X, upper_lPoSC.Y}, {NeckBonePrijected.X, NeckBonePrijected.Y}, SCOLOR, BoneThick);
                                draw->AddLine({upper_rPoSC.X, upper_rPoSC.Y}, {lowerarm_rPoSC.X, lowerarm_rPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({lowerarm_rPoSC.X, lowerarm_rPoSC.Y}, {hand_rPoSC.X, hand_rPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({upper_lPoSC.X, upper_lPoSC.Y}, {lowerarm_lSC.X, lowerarm_lSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({lowerarm_lSC.X, lowerarm_lSC.Y}, {hand_lPoSC.X, hand_lPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({thigh_rPoSC.X, thigh_rPoSC.Y}, {thigh_lPoSC.X, thigh_lPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({thigh_lPoSC.X, thigh_lPoSC.Y}, {calf_lPoSC.X, calf_lPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({calf_lPoSC.X, calf_lPoSC.Y}, {foot_lPoSC.X, foot_lPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({thigh_rPoSC.X, thigh_rPoSC.Y}, {calf_rPoSC.X, calf_rPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({calf_rPoSC.X, calf_rPoSC.Y}, {foot_rPoSC.X, foot_rPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({NeckBonePrijected.X, NeckBonePrijected.Y}, {PelvisPoSC.X, PelvisPoSC.Y}, SCOLOR, BoneThick);
                                draw->AddLine({NeckBonePrijected.X, NeckBonePrijected.Y}, {HeadBoneProjected.X, HeadBoneProjected.Y}, SCOLOR, BoneThick);
                            }
                        }


                    FVector Screen;
                    int distanceX;
                    if (!WorldToScreenPlayer(PlayerPos, Screen, &distanceX))
                        continue;

                    ImVec2 PlayerPosSC;
                    auto HeadPos = Player->GetBonePos("Head", {});
                    HeadPos.Z += 60.f;
                    ImVec2 HeadPosSC;
                    auto RootPos = Player->GetBonePos("Root", {});
                    ImVec2 RootPosSC;
                    
                    if (W2S(PlayerPos, (FVector2D *)&PlayerPosSC) && W2S(HeadPos, (FVector2D *)&HeadPosSC) && W2S(RootPos, (FVector2D *)&RootPosSC))
                    {
                        float BoxHeight = RootPosSC.y - HeadPosSC.y;
                        float BoxWidth = BoxHeight / 2;
                        FVector2D BoxStartPos = FVector2D(PlayerPosSC.x - BoxWidth / 2, PlayerPosSC.y - BoxHeight / 2);
                        ImVec2 PlayerTop = ImVec2(PlayerPosSC.x, PlayerPosSC.y - BoxHeight / 2);
                        ImVec2 PlayerBottom = ImVec2(PlayerPosSC.x, PlayerPosSC.y + BoxHeight / 2);

                        if (visual::bLine)
                        {
                            draw->AddLine({(float)glWidth / 2, 0}, ImVec2(PlayerPosSC.x, PlayerPosSC.y - BoxHeight / 2), FinalAlertColor, 1.5f);
                        }

                        if (visual::bBox) {
    CornerBox(BoxStartPos.X, BoxStartPos.Y, BoxHeight / 2, BoxHeight, 1.5f, 0.5f / 2, IM_COL32(255, 255, 255, 255));
}


                        if (visual::bHealth)
                        {
                            float HPTHICKNESS = 2.6f;
                            float fixposyyy = 5;
                            float heightt = (BoxHeight + fixposyyy);

                            DrawFilledRectangle(BoxStartPos.X - 4, PlayerTop.y, HPTHICKNESS, heightt, ImVec4(0, 0, 0, 255));
                            if (Player->Health == 0 && !Player->bDead)
                            {
                                float CurHp = Player->NearDeathBreath;
                                float MaxHP = Player->NearDeatchComponent->BreathMax;
                                DrawFilledRectangle(BoxStartPos.X - 4, PlayerTop.y, HPTHICKNESS, (BoxHeight + fixposyyy) * CurHp / MaxHP, ImVec4(255, 0, 0, 155));
                            }
                            else
                            {
                                float height_of_health = (BoxHeight + fixposyyy) * Player->Health / Player->HealthMax;
                                if (Player->Health > 70.0)
                                    DrawFilledRectangle(BoxStartPos.X - 4, PlayerTop.y + (heightt - height_of_health), HPTHICKNESS, (BoxHeight + fixposyyy) * Player->Health / Player->HealthMax, ImVec4(0, 255, 0, 255));
                                if (Player->Health > 30.0 && Player->Health <= 70.0)
                                    DrawFilledRectangle(BoxStartPos.X - 4, PlayerTop.y + (heightt - height_of_health), HPTHICKNESS, (BoxHeight + fixposyyy) * Player->Health / Player->HealthMax, ImVec4(255, 25, 0, 255));
                                if (Player->Health > 0.0 && Player->Health <= 30.0)
                                    DrawFilledRectangle(BoxStartPos.X - 4, PlayerTop.y + (heightt - height_of_health), HPTHICKNESS, (BoxHeight + fixposyyy) * Player->Health / Player->HealthMax, ImVec4(255, 0, 0, 255));
                            }
                        }

                        if (visual::bPlayerName)
                        {
                            auto color = IsBot(Player) ? ImColor(0, 128, 255, 255) : ImColor(255, 255, 0, 255);
                            std::string name = IsBot(Player) ? " Ai" : Player->PlayerName.ToString();
                            DrawBorderString(GetBoldFont, text_size, name, PlayerBottom.x, PlayerBottom.y + HeightOfName, color);
                            HeightOfName += text_size;
                        }

                        if (visual::bDistance)
                        {
                            std::string TextToDraw = std::to_string((int)Distance) + "m";
                            DrawBorderString(GetBoldFont, text_size, TextToDraw, PlayerBottom.x, PlayerBottom.y + HeightOfName, ImColor(255, 255, 255, 255));
                            HeightOfName += text_size;
                        }
                    } 
                }

                if (visual::bVehicle && Actor->IsA(ASTExtraVehicleBase::StaticClass()))
                {
                    auto m_Vehicle = (ASTExtraVehicleBase *)Actor;

                    if (!m_Vehicle->Mesh)
                        continue;
                    float Distance = localPlayer->GetDistanceTo(m_Vehicle) / 100.f;
                    if (Distance < 10.0f || Distance > 450.0f)
                        continue;
                    auto velocity = m_Vehicle->GetVelocity();
                    float velCalSize = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);
                    float km_h = (velCalSize * 60.f * 60.f) / (100.f * 1000.f);
                    bool running = km_h > 3.f;
                    FVector2D vehiclePos;
                    if (W2S(m_Vehicle->RootComponent->RelativeLocation, &vehiclePos))
                    {
                        DrawBorderString(GetBoldFont, text_size,
                                         std::string(GetVehicleName(m_Vehicle)) + " - " + std::to_string((int)Distance) + "m",
                                         vehiclePos.X,
                                         vehiclePos.Y,
                                         km_h > 3.f ? (ImColor(255, 38, 0)) : (ImColor(255, 255, 0)));
                    }
                    continue;
                }
                
if (visual::OpenAllAlert)
{
    if (Actor->IsA(ASTExtraGrenadeBase::StaticClass()))
    {
        std::string GrenadeType;
        auto Genn = (ASTExtraGrenadeBase *)Actor;
        if (!Genn->RootComponent)
            continue;
            
        float Distance = Genn->GetDistanceTo(localPlayer) / 100.f;
        if (Distance >= 60.f)
            continue;

        bool isBlinkVisible = ((int)(ImGui::GetTime() * 3.0f) % 2 == 0);
        ImColor warncolor = isBlinkVisible ? IM_COL32(255, 0, 0, 255) : IM_COL32(255, 225, 0, 255);
        
        std::string Grenadewarning = ICON_FA_EXCLAMATION_TRIANGLE " CẨN THẬN CÓ LỰU ĐẠN " ICON_FA_EXCLAMATION_TRIANGLE;
        
        if (isEqual(Genn->ClassPrivate->GetName(), "BP_Grenade_Shoulei_C"))
            GrenadeType = "Lựu Đạn Phá Mảnh";
        else if (isEqual(Genn->ClassPrivate->GetName(), "BP_Grenade_Burn_C"))
            GrenadeType = "Bom Xăng";
        else if (isEqual(Genn->ClassPrivate->GetName(), "BP_Grenade_Smoke_C"))
            GrenadeType = "Bom Khói";

        FVector2D GrenadePos;
        if (W2S(Genn->K2_GetActorLocation(), &GrenadePos))
        {
            std::string s = GrenadeType + " (" + std::to_string((int)Distance) + "m)";
            
            if (GrenadeType == "Lựu Đạn Phá Mảnh") {
                Circle3D(draw, Genn->K2_GetActorLocation(), 730, ImColor(255, 255, 0, 255), 5);
                draw->AddText(NULL, 25.0f, ImVec2(((float)glWidth / 2) - (ImGui::CalcTextSize(Grenadewarning.c_str()).x / 2.f), 130), warncolor, Grenadewarning.c_str());
            }
            if (GrenadeType == "Bom Xăng") {
                Circle3D(draw, Genn->K2_GetActorLocation(), 390, ImColor(255, 255, 0, 255), 5);
                draw->AddText(NULL, 25.0f, ImVec2(((float)glWidth / 2) - (ImGui::CalcTextSize(Grenadewarning.c_str()).x / 2.f), 130), warncolor, Grenadewarning.c_str());
            }
            
            draw->AddText(NULL, 17.0f, ImVec2(GrenadePos.X, GrenadePos.Y), IM_COL32(255, 255, 0, 255), s.c_str());
        }
    }
}

                

                if (visual::bARNear)
                {
                    if (Actor->IsA(APickUpWrapperActor::StaticClass()))
                    {
                        auto PickUp = (APickUpWrapperActor *)Actor;
                        auto id = PickUp->DefineID.TypeSpecificID;
                        if ((id >= 101001 && id <= 101010) || id == 101100 || id == 105001 || id == 105002 || id == 101102)
                        {
                            ARNearestCache.push_back(PickUp);
                        }
                    }
                }
            }
        }
    }

    if (visual::bARNear)
    {
        ARNearestList = ARNearestCache;
        int LargetDistance = 300;
        APickUpWrapperActor *near_item = nullptr;
        for (auto &ARNearest : ARNearestList)
        {
            float Distance = ARNearest->GetDistanceTo(localPlayer) / 100.0f;
            if (Distance < LargetDistance) {
                LargetDistance = Distance;
                near_item = ARNearest;
            }
        }
        if (near_item)
        {
            FVector2D itemPos;
            if (W2S(near_item->K2_GetActorLocation(), &itemPos))
            {
                draw->AddLine({(float)glWidth / 2, (float)(glHeight / 0.5f)}, ImVec2(itemPos.X, itemPos.Y), IM_COL32(255, 0, 0, 255), 0.5f);
            }
        }
        ARNearestCache.clear();
    }

    if (visual::MatchInfo)
    {
        bool showsta = true;
        if (showsta) ShowState(&showsta);
    }

if (visual::Enemy && localPlayer != nullptr)
{
    int totalPlayers = totalEnemies + totalBots;

    ImVec4 borderColor;
    char text[64];

    if (totalPlayers == 0)
    {
        borderColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); 
        snprintf(text, sizeof(text), "NO ONE IS NEAR YOU");
    }
    else
    {
        borderColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); 
        snprintf(text, sizeof(text), "BOTS: %d  PLAYER: %d", totalBots, totalEnemies);
    }

    static ImVec2 windowPos(glWidth * 0.5f, 100.0f);

    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, ImVec2(0.5f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.97f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 6));

    ImGui::Begin("##EnemyCounter", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoFocusOnAppearing |
                     ImGuiWindowFlags_NoNav);

ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", text);

    if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        windowPos.x += delta.x;
        windowPos.y += delta.y;
    }

    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();

    draw->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                  IM_COL32((int)(borderColor.x * 255), (int)(borderColor.y * 255), (int)(borderColor.z * 255), 255),
                  0.0f, 0, 2.5f);

    ImGui::End();
    ImGui::PopStyleVar(2);
}

    g_LocalController = LocalController;
    g_localPlayer = localPlayer;
}

#include <string>
#include <vector>

bool carspring;
std::string item_seprated_by_zero(std::vector<FSkinItem> skins)
{
  std::string out;
  for (int i = 0; i < skins.size(); i++)
  {
    std::string val = skins[i].name;
    out += val;
    if (i < skins.size())
    {
      out += '\0';
    }
  }
  return out;
}

void RenderSkinItem(const std::string& label, CSkinsInfo& skins, on_change_callback cb = nullptr) {
    static std::map<std::string, std::string> custom_buffers;
    static std::set<std::string> bufferInited;
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("%s", label.c_str());
    ImGui::TableSetColumnIndex(1);
    ImGui::PushItemWidth(-1);
    std::string preview = "NULL";
    if (!skins.items.empty() && skins.current_index >= 0 && skins.current_index < (int)skins.items.size())
        preview = skins.items[skins.current_index].name;
    std::string comboId = "##" + label + "combo";
    if (ImGui::BeginCombo(comboId.c_str(), preview.c_str())) {
        for (int i = 0; i < (int)skins.items.size(); i++) {
            bool selected = (skins.current_index == i);
            if (ImGui::Selectable(skins.items[i].name.c_str(), selected)) {
                skins.current_index = i;
                if (skins.out) {
                    *skins.out = skins.items[i].value;
                    WriteConfig(label, *skins.out);
                }
                custom_buffers[label] = std::to_string(skins.items[i].value);
                if (cb) cb(0);
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::PopItemWidth();
    ImGui::TableSetColumnIndex(2);
    if (bufferInited.find(label) == bufferInited.end()) {
        if (skins.out) custom_buffers[label] = std::to_string(*skins.out);
        else custom_buffers[label] = "";
        bufferInited.insert(label);
    }
    char inputBuf[64];
    strncpy(inputBuf, custom_buffers[label].c_str(), sizeof(inputBuf) - 1);
    inputBuf[sizeof(inputBuf) - 1] = '\0';
    float btnW = 25.0f;
    std::string inputId = "##" + label + "input";
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - btnW - 3.0f);
    if (ImGui::KeypadEditString(inputId.c_str(), &custom_buffers[label])) {
        const char* inputBuf = custom_buffers[label].c_str();
        if (skins.out && inputBuf[0] != '\0') {
            try {
                DWORD val = std::stoul(inputBuf);
                *skins.out = val;
                WriteConfig(label, val);
                skins.current_index = -1;
                for (int i = 0; i < (int)skins.items.size(); i++) {
                    if (skins.items[i].value == val) {
                        skins.current_index = i;
                        break;
                    }
                }
                if (cb) cb(0);
            } catch (...) {}
        }
    }
    ImGui::PopItemWidth();
    ImGui::SameLine(0, 3.0f);
    ImGui::PushFont(Icon);
    std::string btnId = "##paste" + label;
    if (ImGui::Button((ICON_FA_PASTE + btnId).c_str(), ImVec2(btnW, 0))) {
        const char* clip = ImGui::GetClipboardText();
        if (clip && clip[0] != '\0') {
            try {
                DWORD val = std::stoul(clip);
                if (skins.out) *skins.out = val;
                custom_buffers[label] = std::to_string(val);
                skins.current_index = -1;
                for (int i = 0; i < (int)skins.items.size(); i++) {
                    if (skins.items[i].value == val) {
                        skins.current_index = i;
                        break;
                    }
                }
                if (cb) cb(0);
                NotifySuccess("Pasted!");
            } catch (...) {
                NotifyError("Invalid!");
            }
        }
    }
    ImGui::PopFont();
}

void* CreateMemoryPage(void* realAddress) {
    size_t page_size = sysconf(_SC_PAGESIZE);
    void* aligned_address = (void*)((uintptr_t)realAddress & ~(page_size - 1));
    void* fakePage = mmap(nullptr, page_size, PROT_READ | PROT_WRITE,
      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (fakePage == MAP_FAILED) {
        return nullptr;
    }
    memcpy(fakePage, aligned_address, page_size);
    return fakePage;
}

template <typename T>
void OnVehicleSkinChange(int newId) {
    if (!skin.bVehicleSkin) return;
    auto localPlayer = g_localPlayer;
    if (!localPlayer) return;
    if (localPlayer->CurrentVehicle && localPlayer->CurrentVehicle->VehicleAvatar) {
        int ava = localPlayer->CurrentVehicle->VehicleAvatar->GetDefaultAvatarID();
        int neww = GetVehSkinModded(ava);
        if (neww > 0) localPlayer->CurrentVehicle->VehicleAvatar->ChangeItemAvatar(neww, 0);
    }
}

void OnClothSkinChange(int newId) {
    return;
}

struct OnlineSkinInfo { std::string name; std::string id; };

static char keyBuffer[128] = "";
void draw_login() {
    ImGui::SetNextWindowSize(ImVec2(400, 315), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    
    if (ImGui::Begin("ACTIVE KEY", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::Text("Enter your license"); 
        
        ImGui::PushItemWidth(-1);
        ImGui::InputText("##keyBuffer", keyBuffer, IM_ARRAYSIZE(keyBuffer));
        ImGui::PopItemWidth();

        static std::string err = "";

        if (ImGui::Button("Paste", ImVec2(-1, 50))) { 
            std::string key = getClipboardText();
            if(!key.empty()) {
                strncpy(keyBuffer, key.c_str(), sizeof(keyBuffer) - 1);
                keyBuffer[sizeof(keyBuffer) - 1] = '\0';
            }
        }

        if (ImGui::Button("Login", ImVec2(-1, 50))) { 
            err = Login(keyBuffer);
            if (err == "OK") {
                isLogin = (bValid && g_Auth == g_Token);
            }
        }

        if (!err.empty() && err != "OK") {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
            ImGui::TextWrapped("Error: %s", err.c_str());
            ImGui::PopStyleColor();
        }        
    }
    ImGui::End();
}


void ParseSkins(const std::string& content, std::vector<OnlineSkinInfo>& skins) {
    skins.clear();
    std::stringstream ss(content);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        size_t separator_pos = line.find('|');
        if (separator_pos != std::string::npos) {
            std::string id = line.substr(0, separator_pos);
            std::string name = line.substr(separator_pos + 1);

            id.erase(0, id.find_first_not_of(" \t\n\r"));
            id.erase(id.find_last_not_of(" \t\n\r") + 1);

            name.erase(0, name.find_first_not_of(" \t\n\r"));
            name.erase(name.find_last_not_of(" \t\n\r") + 1);
            
            if (!name.empty() && !id.empty()) {
                skins.push_back({name, id});
            }
        }
    }
}

std::string ReadStringFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string GetPackageNameString() {
    FILE *f = fopen("/proc/self/cmdline", "rb");
    if (f) {
        char buf[64] = {0};
        fread(buf, sizeof(char), 63, f);
        fclose(f);
        return std::string(buf);
    }
    return "";
}

void *SkinDumpkod(void *)
{
    doing = 0;
    total = 0;
    skipped = 0;
    
    std::string packageName = GetPackageName();
    if (packageName.empty()) {
        LOGI(OBFUSCATE("Failed to get package name"));
        return nullptr;
    }
    
    std::string dumpPath = "/storage/emulated/0/Android/data/" + 
                           packageName + 
                           "/files/log/Dump.txt";
    
    std::wofstream file(dumpPath);
    
    if (!file.is_open()) {
        LOGI(OBFUSCATE("Failed to open Dump.txt at path: %s"), dumpPath.c_str());
        return nullptr;
    }
    
    auto backpack = (UBackpackUtils *)UBackpackUtils::StaticClass();
    if (!backpack) {
        LOGI(OBFUSCATE("Failed to get backpack"));
        file.close();
        return nullptr;
    }
    
    TArray<int> items = backpack->GetItemIDs();
    total = items.Num();
    
    for (int i = 0; i < items.Num(); i++)
    {
        auto data = backpack->GetItemRecord(items[i]);
        if (data.BPID == 0)
        {
            skipped++;
            continue;
        }
        file << items[i] << " | " << std::wstring(data.ItemName.ToWString()) << '\n';
        doing++;
    }
    
    file.close();
    return nullptr;
}


ImVec4 to_vec4(float r, float g, float b, float a) {
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

namespace Setting {
    int Tab = 1;
    bool ExitMain;
}

struct {int screenWidth,screenHeight;}egl;
ImVec2 windowPos = ImVec2(50,50);
ImVec2 touchStart;
bool isDragging = false;
ImVec2 SmoothMove(ImVec2 start,ImVec2 end,float speed) {
return ImVec2(start.x + (end.x - start.x) * speed,start.y + (end.y - start.y) * speed);
}

EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    
    if (glWidth <= 0 || glHeight <= 0) return orig_eglSwapBuffers(dpy, surface);
    if (!g_App) return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

        if (!initImGui) {
        InitTexture();
        ImGui::CreateContext();
        ImGui::GetIO().ConfigErrorRecoveryEnableAssert = false;
        ImGui::GetIO().ConfigErrorRecoveryEnableTooltip = false;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(10, 8);
        style.FramePadding = ImVec2(8, 6);
        style.ItemSpacing = ImVec2(6, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.ScrollbarSize = 22.0f;
        style.GrabMinSize = 10.0f;
        style.WindowRounding = 2.0f;
        style.FrameRounding = 2.0f;
        style.ChildRounding = 2.0f;
        style.PopupRounding = 2.0f;
        style.TabRounding = 2.0f;
        style.WindowBorderSize = 1.5f;
        style.FrameBorderSize = 1.2f;
        style.ChildBorderSize = 1.2f;
        style.PopupBorderSize = 1.2f;
        style.TabBorderSize = 1.2f;
        ImVec4* c = style.Colors;

style.Colors[ImGuiCol_WindowBg]          = ImVec4(0.03f, 0.04f, 0.06f, 0.90f);

style.Colors[ImGuiCol_Border]            = ImVec4(0, 0, 0, 0);
style.Colors[ImGuiCol_BorderShadow]      = ImVec4(0, 0, 0, 0);

style.Colors[ImGuiCol_FrameBg]           = ImVec4(0.12f, 0.13f, 0.15f, 0.80f);
style.Colors[ImGuiCol_FrameBgHovered]    = ImVec4(0.20f, 0.30f, 0.50f, 0.60f);
style.Colors[ImGuiCol_FrameBgActive]     = ImVec4(0.20f, 0.40f, 0.80f, 0.80f);

style.Colors[ImGuiCol_TitleBg]           = ImVec4(0.05f, 0.06f, 0.08f, 1.00f);
style.Colors[ImGuiCol_TitleBgActive]     = ImVec4(0.08f, 0.10f, 0.15f, 1.00f);
style.Colors[ImGuiCol_TitleBgCollapsed]  = ImVec4(0.03f, 0.03f, 0.05f, 1.00f);

style.Colors[ImGuiCol_Text]              = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
style.Colors[ImGuiCol_TextDisabled]      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

style.Colors[ImGuiCol_Button]            = ImVec4(0.10f, 0.12f, 0.15f, 0.80f);
style.Colors[ImGuiCol_ButtonHovered]     = ImVec4(0.20f, 0.35f, 0.70f, 0.60f);
style.Colors[ImGuiCol_ButtonActive]      = ImVec4(0.20f, 0.45f, 0.90f, 0.90f);

style.Colors[ImGuiCol_Tab]               = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
style.Colors[ImGuiCol_TabHovered]        = ImVec4(0.20f, 0.35f, 0.70f, 0.80f);
style.Colors[ImGuiCol_TabActive]         = ImVec4(0.20f, 0.45f, 0.90f, 1.00f);

style.Colors[ImGuiCol_CheckMark]         = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);

style.Colors[ImGuiCol_Separator]         = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
style.Colors[ImGuiCol_SeparatorHovered]  = ImVec4(0.20f, 0.50f, 1.00f, 0.80f);
style.Colors[ImGuiCol_SeparatorActive]   = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);

style.Colors[ImGuiCol_PopupBg]           = ImVec4(0.08f, 0.08f, 0.10f, 0.95f);
style.Colors[ImGuiCol_ModalWindowDimBg]  = ImVec4(0, 0, 0, 0.60f);

ImGui_ImplAndroid_Init(g_App->window);
ImGui_ImplOpenGL3_Init("#version 300 es");
   
io.ConfigWindowsMoveFromTitleBarOnly = true;
io.IniFilename = NULL;

static const ImWchar icons_ranges[] = { 0xf000, 0xf8ff, 0 };

ImFontConfig icons_config;
ImFontConfig font_config;
ImFontConfig CustomFont;
CustomFont.FontDataOwnedByAtlas = false;
icons_config.MergeMode = true;
icons_config.PixelSnapH = true;
icons_config.OversampleH = 3.0;
icons_config.OversampleV = 3.0;
        
io.Fonts->AddFontFromMemoryCompressedTTF(roboto_bin_compressed_data, roboto_bin_compressed_size, 22.0f, NULL, io.Fonts->GetGlyphRangesVietnamese());

io.Fonts->AddFontFromMemoryTTF(
    (void*)font_awesome_6,
    sizeof(font_awesome_6),
    22.0f,
    &icons_config,
    icons_ranges
);

io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t *>(Custom), sizeof(Custom), 22.0f, &CustomFont);

GetBoldFont = io.Fonts->AddFontFromMemoryTTF((void *)OPPOSans_H, OPPOSans_H_size, 26.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());

QuestrialRegular = io.Fonts->AddFontFromMemoryTTF((void *)QuestrialRegular_data, QuestrialRegular_size, 22.0f, &font_config);

initImGui = true;
}

ImGuiIO &io = ImGui::GetIO();
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
ImGui::NewFrame();

// Floating Button
ImGui::Begin("##OpenButton", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);
ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0,0,0,0));
ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0,0,0,0));

if (!show && ImGui::ImageButton("##Open", (void*)(intptr_t)Picsart.textureId, ImVec2(88,88), ImVec2(0,0), ImVec2(1,1))) {
    show = true;
}
ImGui::PopStyleColor(3);
ImGui::PopStyleVar();
ImGui::End();

DrawESP(ImGui::GetBackgroundDrawList());

// Menu
if (show) {
    if (!isLogin) draw_login();
    else {
        ImGui::SetNextWindowSize(ImVec2(820.0f, 560.0f), ImGuiCond_Once);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
        char buf[128];
        sprintf(buf, OBFUSCATE("UNIT MOD 4.5.0 (com.tencent.ig) - FPS %.1f ###Title"), io.Framerate);
        ImGui::Begin(buf, &show, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse); {


        
static int tab = 1;            
ImVec4 activeText = ImVec4(0.0f, 0.6f, 1.0f, 1.0f);
ImVec4 normalText = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);

ImVec4 transparent = ImVec4(0, 0, 0, 0);

float menuWidth = ImGui::GetContentRegionAvail().x;
float spacing = ImGui::GetStyle().ItemSpacing.x;
float btnW = (menuWidth - (spacing * 5)) / 6.0f;

ImGui::Separator();


ImGui::PushStyleColor(ImGuiCol_Button, transparent);
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1,1,1,0.05f)); 
ImGui::PushStyleColor(ImGuiCol_ButtonActive, transparent);
static bool firstHomeOpen = true;
static bool showLoading = false;
static float progress = 0.0f;

// === HOME ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 1 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_HOME " ДОМ " : ICON_FA_HOME " HOME", ImVec2(btnW, 50)))
tab = 1;
ImGui::PopStyleColor();
ImGui::SameLine();

// === ESP ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 2 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_EYE " игроков "  : ICON_FA_EYE  " ESP" , ImVec2(btnW, 50)))    
tab = 2;    
ImGui::PopStyleColor();
ImGui::SameLine();

// === AIM ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 3 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_CROSSHAIRS  " Аим"  : ICON_FA_CROSSHAIRS  " AIM" , ImVec2(btnW, 50)))
tab = 3;    
ImGui::PopStyleColor();
ImGui::SameLine();

// === MEMORY ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 4 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_MEMORY  " Хак памяти"  : ICON_FA_MEMORY  " MEMORY " , ImVec2(btnW, 50)))
tab = 4; 
ImGui::PopStyleColor();
ImGui::SameLine();

// === SKIN ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 5 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_TSHIRT  " Скин"  : ICON_FA_TSHIRT  " SKIN" , ImVec2(btnW, 50)))
tab = 5;   
ImGui::PopStyleColor();
ImGui::SameLine(); 

// === SETTING ===
ImGui::PushStyleColor(ImGuiCol_Text, tab == 6 ? activeText : normalText);
if (ImGui::Button(languages == 1 ? ICON_FA_COG  " Настройки"  : ICON_FA_COG  " SETTING" , ImVec2(btnW, 50)))
tab = 6;
ImGui::PopStyleColor();

ImGui::Spacing();
ImGui::Spacing();
ImGui::Separator();
// ==========================================
// TAB 1: HOME
// ==========================================
if (tab == 1)
{
    if (firstHomeOpen)
    {
        firstHomeOpen = false;
        showLoading = true;
        progress = 0.0f;
        ImGui::OpenPopup("LoadingPopup");
    }
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Cheat status");
    ImGui::Spacing();
    {
        ImVec2 avail = ImGui::GetContentRegionAvail();
        float colWidth = avail.x / 4.0f;
        ImGui::PushID("status_global");
        DrawDotLabel("GLOBAL", IM_COL32(80, 220, 80, 255), 7.0f, 8.0f);
        ImGui::PopID();
        ImGui::SameLine(150,0); 
        ImGui::PushID("status_kj");
        DrawDotLabel("KOREA/JAPAN", IM_COL32(240, 200, 60, 255), 7.0f, 8.0f);
        ImGui::PopID();
        ImGui::SameLine(350,0); 
        ImGui::PushID("status_tw");
        DrawDotLabel("TAIWAN", IM_COL32(80, 220, 80, 255), 7.0f, 8.0f);
        ImGui::PopID();
        ImGui::SameLine(500,0); 
        ImGui::PushID("status_vn");
        DrawDotLabel("VIETNAM", IM_COL32(80, 220, 80, 255), 7.0f, 8.0f);
        ImGui::PopID();
        ImGui::NewLine();
    }//End Status 
    ImGui::Separator();
    ImGui::Text("Description");
    ImGui::Spacing();
    {
        DrawDotLabel("Safe", IM_COL32(80, 220, 80, 255), 7.0f, 8.0f);
        ImGui::SameLine(250,0); 
        DrawDotLabel("Warning", IM_COL32(240, 200, 60, 255), 7.0f, 8.0f);
        ImGui::SameLine(500,0); 
        DrawDotLabel("Danger", IM_COL32(220, 60, 60, 255), 7.0f, 8.0f);
        ImGui::NewLine();
    }
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("VERSION 4.4.0");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextUnformatted("- AVOID REPORT, PLAY SAFE");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextUnformatted("- TELEGRAM : @MTMOD_VIP");
    ImGui::Spacing();
}
if (showLoading)
{
    if (ImGui::BeginPopupModal("LoadingPopup", NULL,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Loading Process...");
        ImGui::Separator();

        progress += ImGui::GetIO().DeltaTime * 0.2f;

        if (progress >= 1.0f)
        {
            progress = 1.0f;
            showLoading = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::ProgressBar(progress, ImVec2(280, 18));

        ImGui::EndPopup();
    }
}
// ==========================================
// TAB 2: ESP
// ==========================================
if (tab == 2)
{
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(8, 8));
    
    // ROW 3
    ImGui::Checkbox(languages == 1 ? "ЛИНИЯ" : "Line", &config_t::esp::visual::bLine);
    ImGui::SameLine(300, 0);
    ImGui::Checkbox(languages == 1 ? "ИМЯ" : "Name", &config_t::esp::visual::bPlayerName);
    ImGui::SameLine(600, 0);
    ImGui::Checkbox(languages == 1 ? "ИМЯ" : "Weapon", &config_t::esp::visual::bEnemyWeapon);
    
    ImGui::Checkbox(languages == 1 ? "СКЕЛЕТ" : "Skeleton", &config_t::esp::visual::bSkeleton);
    ImGui::SameLine(300, 0);
    ImGui::Checkbox(languages == 1 ? "КОРОБКА" : "Box", &config_t::esp::visual::bBox);
    ImGui::SameLine(600, 0);
    ImGui::Checkbox(languages == 1 ? "ЗДОРОВЬЕ" : "Health", &config_t::esp::visual::bHealth);
    
    ImGui::Checkbox(languages == 1 ? "СЧЁТЧИК ВЫСТРЕЛОВ" : "Enemy gun", &config_t::esp::visual::bSungDich);
    ImGui::SameLine(300, 0);
    ImGui::Checkbox(languages == 1 ? "СЧЁТЧИК ВЫСТРЕЛОВ" : "Team ID", &config_t::esp::visual::bTeamID);
    ImGui::SameLine(600, 0);
    ImGui::Checkbox(languages == 1 ? "РАССТОЯНИЕ" : "Player Distance", &config_t::esp::visual::bDistance);
    
    ImGui::Checkbox(languages == 1 ? "ВСЕ ПРЕДУПРЕЖДЕНИЯ" : "Alert", &config_t::esp::visual::bAlert);
    ImGui::SameLine(300, 0);
    ImGui::Checkbox(languages == 1 ? "СКРЫТЬ БОТОВ" : "Hide/Bot", &config_t::esp::visual::bIgnoreAI);
    ImGui::SameLine(600, 0);
    ImGui::Checkbox(languages == 1 ? "ВРАГ РЯДОМ" : "Player Contry", &config_t::esp::visual::bARNear);
          
    ImGui::Checkbox(languages == 1 ? "ТРАНСПОРТ" : "Vehicle", &config_t::esp::visual::bVehicle);
    ImGui::SameLine(300, 0);
    ImGui::Checkbox(languages == 1 ? "ESP ВРАГ" : "Show enemy count", &config_t::esp::visual::Enemy);
    ImGui::SameLine(600, 0);
    ImGui::Checkbox(languages == 1 ? "ИНФОРМАЦИЯ О МАТЧЕ" : "Game information", &config_t::esp::visual::MatchInfo);        
    
    ImGui::Spacing();    
            
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); 
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.2f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.2f, 0.2f, 0.2f, 0.3f));

    if (ImGui::BeginTabBar("EspSetting")) 
    {
        if (config_t::esp::visual::bPlayerName)
        {
            if (ImGui::BeginTabItem("Name"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                ImGui::ColorEdit4("###Text color", (float *)&Color::nam, ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::Text("Text color");
                
                ImGui::PushItemWidth(650);
                ImGui::ColorEdit4("###Border color", (float *)&Color::nam_border, ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::Text("Border color");
                
                ImGui::PushItemWidth(650);
                ImGui::SliderFloat("###4", &Setting::nsize, 0, 20);
                ImGui::SameLine();
                ImGui::Text("Text size");
                
                ImGui::EndTabItem();
            }
        }
        
        if (config_t::esp::visual::bSungDich)
        {
            if (ImGui::BeginTabItem("Weapon"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                ImGui::ColorEdit4("###Weapon color", (float *)&Setting::WeaponColor, ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::Text("Text color");
                
                ImGui::PushItemWidth(650);
                ImGui::SliderInt("###Weapon", &Setting::weaponsize, 0, 20);
                ImGui::SameLine();
                ImGui::Text("Text size");
                
                ImGui::EndTabItem();
            }
        }
        
        if (config_t::esp::visual::bSkeleton)
        {
            if (ImGui::BeginTabItem("Skeleton"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                const char *Emu[] = {"Default", "TeamID"}; 
                const char *combo_label = Emu[Setting::skele];
                
                if (ImGui::BeginCombo("###SkeletonType", combo_label, ImGuiComboFlags_HeightSmall))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(Emu); n++)
                    {
                        const bool is_selected = (Setting::skele == n);
                        if (ImGui::Selectable(Emu[n], is_selected))
                            Setting::skele = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                ImGui::Text("Color mode");
                
                if (Setting::skele == 0)
                {
                    ImGui::PushItemWidth(650);
                    ImGui::ColorEdit4("###color", (float *)&Color::skelec, ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                    ImGui::Text("Skeleton color");
                }
                
                ImGui::PushItemWidth(650);
                ImGui::SliderFloat("###Bone size", &Setting::pbonesize, 1.0f, 5.0f);
                ImGui::SameLine();
                ImGui::Text("Thickness");
                
                ImGui::EndTabItem();
            }
        }
        
        if (config_t::esp::visual::bLine)
        {
            if (ImGui::BeginTabItem("Line"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                const char *Emu1[] = {"Default", "TeamID"}; 
                const char *combo_label = Emu1[Setting::linne];
                
                if (ImGui::BeginCombo("##Line Type", combo_label, ImGuiComboFlags_HeightSmall))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(Emu1); n++)
                    {
                        const bool is_selected = (Setting::linne == n);
                        if (ImGui::Selectable(Emu1[n], is_selected))
                            Setting::linne = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                ImGui::Text("Color mode");
                
                if (Setting::linne == 0)
                {
                    ImGui::PushItemWidth(650);
                    ImGui::ColorEdit4(" ###color1", (float *)&Color::playerline, ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                    ImGui::Text("Line color");
                }
                
                ImGui::PushItemWidth(650);
                ImGui::SliderFloat("###Line size", &Setting::plinesize, 1.0f, 5.00f);
                ImGui::SameLine();
                ImGui::Text("Thickness");
                
                ImGui::EndTabItem();
            }
        }

        if (config_t::esp::visual::bDistance)
        {
            if (ImGui::BeginTabItem("Distance"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                ImGui::ColorEdit4("###Distance Color", (float *)&Color::enemy, ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::Text("Text color");
                
                ImGui::PushItemWidth(650);
                ImGui::SliderInt("###Distance size", &Setting::dissize, 0, 20);
                ImGui::SameLine();
                ImGui::Text("Text size");
                
                ImGui::EndTabItem();
            }
        }
        
        if (config_t::esp::visual::bHealth)
        {
            if (ImGui::BeginTabItem("Health"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                const char *Emu2[] = {"Show as BAR", "Show as TEXT"};
                const char *combo_label = Emu2[Setting::hpbt];
                
                if (ImGui::BeginCombo("###Hekth", combo_label, ImGuiComboFlags_HeightSmall))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(Emu2); n++)
                    {
                        const bool is_selected = (Setting::hpbt == n);
                        if (ImGui::Selectable(Emu2[n], is_selected))
                            Setting::hpbt = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                ImGui::Text("Display mode");
                
                if (Setting::hpbt == 1)
                {
                    ImGui::Separator();
                    ImGui::PushItemWidth(650);
                    ImGui::ColorEdit4("### colorhp", (float *)&Color::HPP, ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                    ImGui::Text("Text color");
                    
                    ImGui::PushItemWidth(650);
                    ImGui::SliderInt("###Health size", &Setting::hp, 0, 20);
                    ImGui::SameLine();
                    ImGui::Text("Text size");
                }
                ImGui::EndTabItem();
            }
        }                        

        if (config_t::esp::visual::bBox)
        {
            if (ImGui::BeginTabItem("Box"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                const char *newemu[] = {"4 edges", "Rectangle"};
                const char *testcombo_label = newemu[Setting::Test];
                
                if (ImGui::BeginCombo(" ###lo5ll", testcombo_label, ImGuiComboFlags_HeightSmall))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(newemu); n++)
                    {
                        const bool is_selected = (Setting::Test == n);
                        if (ImGui::Selectable(newemu[n], is_selected))
                            Setting::Test = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                ImGui::Text("Display mode");
                
                ImGui::EndTabItem();
            }
        }

        if (config_t::esp::visual::bVehicle)
        {
            if (ImGui::BeginTabItem("Vehicle"))
            {
                ImGui::Separator();
                ImGui::PushItemWidth(650);
                ImGui::ColorEdit4(" vehiclec", (float *)&Color::vehicle, ImGuiColorEditFlags_NoLabel);
                ImGui::SameLine();
                ImGui::Text("Text color");
                
                ImGui::PushItemWidth(650);
                ImGui::SliderInt("###vehicle size", &vehisize, 0, 20);
                ImGui::SameLine();
                ImGui::Text("Text size");
                
                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }
    
    ImGui::PopStyleColor(3); 
                        
    ImGui::PopStyleVar();
}

// ==========================================
// TAB 3: AIMBOT
// ==========================================
if (tab == 3)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));    
   
    if (ImGui::BeginChild("##AIM", ImVec2(0, 0), true))
    {
        ImGui::TextColored(ImVec4(0.8f, 0.9f, 0.0f, 1.0f), "Dangers");
        ImGui::Checkbox("Enable aim", &config_t::aim::enabled);
        
        ImGui::Separator();

        // Aim Type
        ImGui::Text("Aim Type");
        ImGui::SetNextItemWidth(-1);
        const char* aimModes[] = { "Aimbot", "Magic Bullet" };
        ImGui::Combo("##Aim Modes", (int*)&config_t::aim::aim_type, aimModes, IM_ARRAYSIZE(aimModes));

        // Aim Target
        ImGui::Text("Aim target");
        ImGui::SetNextItemWidth(-1);
        const char* bones[] = { "Head", "Chest", "Body", "Nearest" };
        ImGui::Combo("##Aimbot Bone", (int*)&config_t::aim::type_target, bones, IM_ARRAYSIZE(bones));

        ImGui::Separator();

        float itemWidth = (ImGui::GetContentRegionAvail().x - 20) / 3;
        
        ImGui::Checkbox("Exclude Bot", &config_t::esp::visual::bIgnoreAI);
        ImGui::SameLine(300, 0);
        ImGui::Checkbox("Ignore Knocked", &config_t::aim::bIgnoreKnocked);
        ImGui::SameLine(600, 0);
        ImGui::Checkbox("Show Circle", &config_t::aim::bFixFakeDamge); 
        
        ImGui::Checkbox("Show FOV", &config_t::aim::bShowTarget);
        ImGui::SameLine(300, 0);
        ImGui::Checkbox("Visible Check", &config_t::aim::bVisCheck);

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Aim Recoil");
        ImGui::SetNextItemWidth(-1);
        ImGui::SliderFloat("##Recoil", &config_t::aim::recoil_comparison_value, 0.0f, 5.0f, "%.2f");

        ImGui::Text("Aim Fov");
        ImGui::SetNextItemWidth(-1);
        ImGui::SliderFloat("##Aim FOV", &config_t::aim::fovSize, 10.0f, 500.0f, "%.0f");

        ImGui::Text("Aim Distance");
        ImGui::SetNextItemWidth(-1);
        ImGui::SliderFloat("##Distance", &config_t::aim::DisAim, 10.0f, 400.0f, "%.0f m");

        ImGui::Text("Smoothness");
        ImGui::SetNextItemWidth(-1);
        ImGui::SliderFloat("##Smooth", &config_t::aim::smoothness, 1.0f, 20.0f, "%.1f");
        
        ImGui::EndChild();
    }
    ImGui::PopStyleVar();
}



// ==========================================
// TAB 4: MEMORY HACKS
// ==========================================
if (tab == 4)
{
ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 8));
    ImGui::GetStyle().ItemSpacing = ImVec2(4, 4);
        ImGui::Separator();
               
        ImGui::TextColored(ImVec4(0.8f,0.9f,0.0f,1.0f), "Dangers");//желтый
if (ImGui::Checkbox("LessRecoil 90%", &config_t::memory::lessricoil))
{
PATCH_LIB("libUE4.so", "0x2A52654", "00 00 00 00");//28C494C
}
ImGui::SameLine();
ImGui::TextColored(ImVec4(0.85f,0.22f,0.22f,1.0f),ICON_FA_EXCLAMATION_TRIANGLE" DANGERS");
ImGui::SameLine(300,0);
if (ImGui::Checkbox("Small Cross", &config_t::memory::tamcong))
{
PATCH_LIB("libUE4.so", "0x2A4DD24", "00 00 A0 E3 1E FF 2F E1");
}
ImGui::SameLine();
ImGui::TextColored(ImVec4(0.85f,0.22f,0.22f,1.0f),ICON_FA_EXCLAMATION_TRIANGLE" DANGERS");
ImGui::SameLine(600,0);
ImGui::Checkbox(languages == 1 ? "ВИД IPAD" : "Ipad View", &config_t::memory::ipad);
{
PATCH_LIB("libUE4.so", "0x6B623B8", "00 00 85 43");
}
if (ImGui::Checkbox("HDR 120 FPS", &config_t::memory::hdr))
{
PATCH_LIB("libUE4.so", "0x3178C7C", "05 00 A0 E3 1E FF 2F E1"); // UHD GRAPHICS
PATCH_LIB("libUE4.so", "0x3178F80", "78 00 A0 E3 1E FF 2F E1"); // 120 FPS
}
ImGui::SameLine(300,0);
ImGui::Checkbox(languages == 1 ? "ШИРОКИЙ ОБЗОР" : "Wide View", &WideView);
        ImGui::NextColumn();

        if (WideView)
        {
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
            ImGui::SliderInt(languages == 1 ? "УГОЛ ОБЗОРА" : "Field of View", &WideValues, 90, 140);
        }
}
        
// ==========================================
// TAB 5: SKINS
// ==========================================
if (tab == 5) 
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 8));
    ImGui::GetStyle().ItemSpacing = ImVec2(4, 4);

    if (ImGui::BeginChild("##SKIN_ROOT", ImVec2(0, 0), true))
    {
        // OPTIONS
        ImGui::Checkbox(languages == 1 ? "ВКЛЮЧИТЬ МОД СКИНОВ" : "Enable mod skin", &skin.bEnable);
        ImGui::SameLine(300, 0);
        ImGui::Checkbox(languages == 1 ? "СКИНЫ ОРУЖИЯ" : "Gun mod", &skin.bGunSkin);
        ImGui::SameLine(600, 0);
        ImGui::Checkbox(languages == 1 ? "СКИНЫ ОДЕЖДЫ" : "Outfit mod", &skin.bClothSkin);

        ImGui::Checkbox(languages == 1 ? "СКИНЫ ТРАНСПОРТА" : "Vehicle mod", &skin.bVehicleSkin);
        ImGui::SameLine(300, 0);
        ImGui::Checkbox(languages == 1 ? "ЭМОЦИИ" : "Emote", &skin.bEmoteSkin);
        ImGui::SameLine(600, 0);
        ImGui::Checkbox(languages == 1 ? "ДЭДБОКС" : "Deadbox", &skin.bDeadbox);

        ImGui::Checkbox(languages == 1 ? "СООБЩЕНИЕ ОБ УБИЙСТВЕ" : "Kill message", &skin.bKillMsg);
        ImGui::SameLine(300, 0);
        ImGui::Checkbox(languages == 1 ? "МОД РЮКЗАКА" : "Backpack mod", &skin.bBackpack);
        ImGui::Separator();
        ImGui::Checkbox(languages == 1 ? "Метро Роял" : "Metro Royal Mode", &skin.bMetro);
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), languages == 1 ? ICON_FA_EXCLAMATION_TRIANGLE " Включите для Metro Royale, отключите для обычного режима" : ICON_FA_EXCLAMATION_TRIANGLE " Turn on if you want to mod skin in metro royal mode, turn off if only normal mode");
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), languages == 1 ? ICON_FA_EXCLAMATION_TRIANGLE " Мод костюма может привести к бану на 1 секунду" : ICON_FA_EXCLAMATION_TRIANGLE " Suit mod may cause 1 second banned");

        if (skin.bEnable) 
        {
            if (ImGui::BeginTabBar("##SkinTabBar", ImGuiTabBarFlags_FittingPolicyScroll)) 
            {
                // 1. GUN SKINS
                if (skin.bGunSkin && ImGui::BeginTabItem(languages == 1 ? "СКИНЫ ОРУЖИЯ" : "Gun mod")) 
                {
                    if (ImGui::BeginChild("##GunSkins", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar))
                    {
                        if (ImGui::BeginTable("##GunTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) 
                        {
                            ImGui::TableSetupScrollFreeze(0, 1);
                            ImGui::TableSetupColumn(languages == 1 ? "ИМЯ" : "Name", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                            ImGui::TableSetupColumn(languages == 1 ? "ВЫБОР" : "Select", ImGuiTableColumnFlags_WidthStretch);
                            ImGui::TableSetupColumn(languages == 1 ? "СВОЙ ID" : "Custom", ImGuiTableColumnFlags_WidthFixed, 200.0f);
                            ImGui::TableHeadersRow();

                            RenderSkinItem(languages == 1 ? "АКМ" : "AKM", skindata.akm);
                            RenderSkinItem(languages == 1 ? "М416" : "M416", skindata.m416);
                            RenderSkinItem(languages == 1 ? "СКАР-Л" : "SCAR", skindata.scarl);
                            RenderSkinItem(languages == 1 ? "М16А4" : "M16A4", skindata.m16);
                            RenderSkinItem(languages == 1 ? "АУГ" : "AUG", skindata.aug);
                            RenderSkinItem(languages == 1 ? "М762" : "M762", skindata.m762);
                            RenderSkinItem(languages == 1 ? "ГРОЗА" : "GROZA", skindata.groza);
                            RenderSkinItem(languages == 1 ? "ACE32" : "ACE32", skindata.ace32);
                            RenderSkinItem(languages == 1 ? "QBZ" : "QBZ", skindata.qbz);
                            RenderSkinItem(languages == 1 ? "ХАНИБАДЖЕР" : "HONEY", skindata.honey);
                            RenderSkinItem(languages == 1 ? "UMP45" : "UMP", skindata.ump45);
                            RenderSkinItem(languages == 1 ? "ВЕКТОР" : "Vector", skindata.vector);
                            RenderSkinItem(languages == 1 ? "ТОМПСОН" : "Thompson", skindata.tommy);
                            RenderSkinItem(languages == 1 ? "УЗИ" : "UZI", skindata.uzi);
                            RenderSkinItem(languages == 1 ? "КАР98К" : "Kar98", skindata.kar98);
                            RenderSkinItem(languages == 1 ? "М24" : "M24", skindata.m24);
                            RenderSkinItem(languages == 1 ? "AWM" : "AWM", skindata.awm);
                            RenderSkinItem(languages == 1 ? "AMR" : "AMR", skindata.amr);
                            RenderSkinItem(languages == 1 ? "МК14" : "MK14", skindata.mk14);
                            RenderSkinItem(languages == 1 ? "МИНИ14" : "MINI14", skindata.mini14);
                            RenderSkinItem(languages == 1 ? "М249" : "M249", skindata.m249);
                            RenderSkinItem(languages == 1 ? "ДП-28" : "DP28", skindata.dp28);
                            RenderSkinItem(languages == 1 ? "МГ3" : "MG3", skindata.mg3);
                            RenderSkinItem(languages == 1 ? "XM1014" : "XM1014", skindata.xm1014);
                            RenderSkinItem(languages == 1 ? "С12К" : "S12K", skindata.s12k);
                            RenderSkinItem(languages == 1 ? "DBS" : "DBS", skindata.dbs);
                            RenderSkinItem(languages == 1 ? "СКОВОРОДА" : "Pan", skindata.pan);

                            ImGui::EndTable();
                        }
                        ImGui::EndChild();
                    }
                    ImGui::EndTabItem();
                }

                // 2. OUTFIT SKINS
                if (skin.bClothSkin && ImGui::BeginTabItem(languages == 1 ? "СКИНЫ ОДЕЖДЫ" : "Outfit mod")) 
                {
                    if (ImGui::BeginChild("##ClothSkins", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar))
                    {
                        if (ImGui::BeginTable("##ClothTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) 
                        {
                            ImGui::TableSetupScrollFreeze(0, 1);
                            ImGui::TableSetupColumn(languages == 1 ? "ИМЯ" : "Name", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                            ImGui::TableSetupColumn(languages == 1 ? "ВЫБОР" : "Select", ImGuiTableColumnFlags_WidthStretch);
                            ImGui::TableSetupColumn(languages == 1 ? "СВОЙ ID" : "Custom", ImGuiTableColumnFlags_WidthFixed, 200.0f);
                            ImGui::TableHeadersRow();

                            RenderSkinItem(languages == 1 ? "КОСТЮМ" : "Cloth", skindata.cloth);
                            RenderSkinItem(languages == 1 ? "ШЛЯПА" : "Hat", skindata.hat);
                            RenderSkinItem(languages == 1 ? "ПЕРЧАТКИ" : "Hand", skindata.gloves);
                            RenderSkinItem(languages == 1 ? "ЛИЦО" : "Face", skindata.face);
                            RenderSkinItem(languages == 1 ? "МАСКА" : "Mask", skindata.mask);
                            RenderSkinItem(languages == 1 ? "ШТАНЫ" : "Pant", skindata.pant);
                            RenderSkinItem(languages == 1 ? "ОБУВЬ" : "Shoe", skindata.shoe);
                            RenderSkinItem(languages == 1 ? "ШЛЕМ 1" : "Helmet 1", skindata.helmet1);
                            RenderSkinItem(languages == 1 ? "ШЛЕМ 2" : "Helmet 2", skindata.helmet2);
                            RenderSkinItem(languages == 1 ? "ШЛЕМ 3" : "Helmet 3", skindata.helmet3);
                            RenderSkinItem(languages == 1 ? "РЮКЗАК 1" : "Backpack 1", skindata.backpack1);
                            RenderSkinItem(languages == 1 ? "РЮКЗАК 2" : "Backpack 2", skindata.backpack2);
                            RenderSkinItem(languages == 1 ? "РЮКЗАК 3" : "Backpack 3", skindata.backpack3);
                            RenderSkinItem(languages == 1 ? "ПАРАШЮТ" : "Parachute", skindata.parachute);
                            RenderSkinItem(languages == 1 ? "ПЛАНЕР" : "Glider", skindata.glider);
                            RenderSkinItem(languages == 1 ? "ПИТОМЕЦ" : "PetSkin", skindata.petSkin);
                            RenderSkinItem(languages == 1 ? "ЭФФЕКТ ХОЛЛА" : "HallEffect", skindata.hallEffect);

                            ImGui::EndTable();
                        }
                        ImGui::EndChild();
                    }
                    ImGui::EndTabItem();
                }

                // 3. VEHICLE SKINS
                if (skin.bVehicleSkin && ImGui::BeginTabItem(languages == 1 ? "СКИНЫ ТРАНСПОРТА" : "Vehicle mod")) 
                {
                    if (ImGui::BeginChild("##VehicleSkins", ImVec2(0, 0), true))
                    {
                        if (ImGui::BeginTable("##VehicleTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) 
                        {
                            ImGui::TableSetupColumn(languages == 1 ? "ИМЯ" : "Name", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                            ImGui::TableSetupColumn(languages == 1 ? "ВЫБОР" : "Select", ImGuiTableColumnFlags_WidthStretch);
                            ImGui::TableSetupColumn(languages == 1 ? "СВОЙ ID" : "Custom", ImGuiTableColumnFlags_WidthFixed, 200.0f);
                            ImGui::TableHeadersRow();

                            RenderSkinItem(languages == 1 ? "КУПЕ RB" : "Coupe-RB", skindata.coupe);
                            RenderSkinItem(languages == 1 ? "УАЗ" : "UAZ", skindata.uaz);
                            RenderSkinItem(languages == 1 ? "ДАЧИЯ" : "DACIA", skindata.dacia);
                            RenderSkinItem(languages == 1 ? "МОТОЦИКЛ" : "MOTOR", skindata.motor);
                            RenderSkinItem(languages == 1 ? "МИРАДО" : "MIRADO", skindata.mirado);
                            RenderSkinItem(languages == 1 ? "БАГГИ" : "BUGGY", skindata.buggy);

                            ImGui::EndTable();
                        }
                        ImGui::EndChild();
                    }
                    ImGui::EndTabItem();
                }

                // 4. EMOTES
                if (skin.bEmoteSkin && ImGui::BeginTabItem(languages == 1 ? "ЭМОЦИИ" : "Emote mod")) 
                {
                    if (ImGui::BeginChild("##emoje", ImVec2(0, 0), true))
                    {
                        if (ImGui::BeginTable("##emoge", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) 
                        {
                            ImGui::TableSetupColumn(languages == 1 ? "ИМЯ" : "Name", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                            ImGui::TableSetupColumn(languages == 1 ? "ВЫБОР" : "Select", ImGuiTableColumnFlags_WidthStretch);
                            ImGui::TableSetupColumn(languages == 1 ? "СВОЙ ID" : "Custom", ImGuiTableColumnFlags_WidthFixed, 200.0f);
                            ImGui::TableHeadersRow();

                            RenderSkinItem(languages == 1 ? "ЭМОЦИЯ 1" : "Emote 1", skindata.emote1);
                            RenderSkinItem(languages == 1 ? "ЭМОЦИЯ 2" : "Emote 2", skindata.emote2);
                            RenderSkinItem(languages == 1 ? "ЭМОЦИЯ 3" : "Emote 3", skindata.emote3);

                            ImGui::EndTable();
                        }
                        ImGui::EndChild();
                    }
                    ImGui::EndTabItem();
                }


                // 6. SEARCH SKINS
                if (SkinDumpss && ImGui::BeginTabItem(ICON_FA_SEARCH " Search skins")) 
                {
                    if (ImGui::BeginChild("##SkinDump", ImVec2(0, 0), true))
                    {
                        static std::string searchBuffer;
                        static std::vector<OnlineSkinInfo> allSkins;
                        static std::vector<int> filteredIndices;
                        static std::atomic<bool> isLoadingSkins(false);
                        static std::mutex skinsMutex;
                        static bool needFilter = true;

                        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 120.0f);
                        searchBuffer.reserve(256);

                        if (ImGui::KeypadEditString("Search skin...", &searchBuffer)) {
                            needFilter = true;
                        }

                        static std::string lastSearchBuffer;
                        if (searchBuffer != lastSearchBuffer) {
                            lastSearchBuffer = searchBuffer;
                            needFilter = true;
                        }

                        ImGui::PopItemWidth();
                        ImGui::SameLine();

                        if (!isLoadingSkins) 
                        {
                            if (ImGui::Button(ICON_FA_DOWNLOAD " Load", ImVec2(-1, 0))) 
                            {
                                isLoadingSkins.store(true);
                                NotifyInfo("Loading skins...");

                                std::thread([]() {
                                    try {
                                        SkinDumpkod(0);
                                        std::string path = "/storage/emulated/0/Android/data/com.tencnt.ig/files/log/Dump.txt";
                                        std::string content = ReadStringFromFile(path);

                                        if (!content.empty()) {
                                            std::vector<OnlineSkinInfo> tempSkins;
                                            ParseSkins(content, tempSkins);

                                            {
                                                std::lock_guard<std::mutex> lock(skinsMutex);
                                                allSkins = std::move(tempSkins);
                                                filteredIndices.clear();
                                                for (int i = 0; i < (int)allSkins.size(); i++)
                                                    filteredIndices.push_back(i);
                                            }
                                            needFilter = true;
                                            NotifySuccess("Skins loaded!");
                                        } else {
                                            NotifyError("Failed to load skins!");
                                        }
                                    } catch (...) {
                                        NotifyError("Error loading skins!");
                                    }
                                    isLoadingSkins.store(false);
                                }).detach();
                            }
                        } else {
                            ImGui::TextDisabled(ICON_FA_SPINNER " Loading...");
                        }

                        ImGui::Separator();

                        if (needFilter) 
                        {
                            std::lock_guard<std::mutex> lock(skinsMutex);
                            filteredIndices.clear();

                            std::string lower = searchBuffer;
                            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

                            for (int i = 0; i < (int)allSkins.size(); i++) {
                                if (lower.empty()) {
                                    filteredIndices.push_back(i);
                                    continue;
                                }
                                std::string nameLow = allSkins[i].name;
                                std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);

                                if (nameLow.find(lower) != std::string::npos || allSkins[i].id.find(lower) != std::string::npos) {
                                    filteredIndices.push_back(i);
                                }
                            }
                            needFilter = false;
                        }

                        {
                            std::lock_guard<std::mutex> lock(skinsMutex);

                            if (allSkins.empty() && !isLoadingSkins) {
                                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Press 'Load' to start.");
                            } else if (filteredIndices.empty() && !searchBuffer.empty()) {
                                ImGui::TextDisabled("No results found.");
                            } else if (ImGui::BeginTable("##SkinsTable", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) {
                                ImGui::TableSetupScrollFreeze(0, 1);
                                ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 150.0f);
                                ImGui::TableSetupColumn("NAME", ImGuiTableColumnFlags_WidthStretch);
                                ImGui::TableHeadersRow();

                                for (int idx : filteredIndices) {
                                    const auto& s = allSkins[idx];
                                    ImGui::TableNextRow();

                                    ImGui::TableSetColumnIndex(0);
                                    ImGui::PushID(idx);
                                    if (ImGui::Selectable(s.id.c_str(), false, ImGuiSelectableFlags_SpanAllColumns)) {
                                        ImGui::SetClipboardText(s.id.c_str());
                                        NotifySuccess("ID Copied!");
                                    }
                                    ImGui::PopID();

                                    ImGui::TableSetColumnIndex(1);
                                    ImGui::TextUnformatted(s.name.c_str());
                                }
                                ImGui::EndTable();
                            }
                        }
                        ImGui::EndChild();
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::EndChild();
    }
    ImGui::PopStyleVar();
}

// ==========================================
// TAB 6: SETTINGS
// ==========================================
if (tab == 6) {
ImVec2 bigBtnSize = ImVec2(-1, 62);
ImVec4 btnColor = ImVec4(0.10f, 0.12f, 0.15f, 0.80f);
ImVec4 btnHover = ImVec4(0.20f, 0.35f, 0.70f, 0.60f);
ImVec4 btnActive = ImVec4(0.20f, 0.45f, 0.90f, 0.90f);

ImGui::PushStyleColor(ImGuiCol_Button, btnColor);
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, btnHover);
ImGui::PushStyleColor(ImGuiCol_ButtonActive, btnActive);

ImGui::Separator();
ImGui::Spacing();

ImGui::Text((const char*)u8"\uf017 Remaining time: 1752578 hours 59 minutes");
ImGui::Spacing();
ImGui::Separator();
ImGui::Spacing();

// Ayarlar kısmı
ImGui::PushItemWidth(170);
ImGui::Text("Language");
ImGui::SameLine(120);
ImGui::Combo("", &languages, "English\0Русский\0");
ImGui::PopItemWidth();

ImGui::SameLine(310);
ImGui::Checkbox("Border string", &Textborder);
ImGui::SameLine(530);
ImGui::Checkbox("Send WWCD", &Funny);
ImGui::SameLine(950);
ImGui::Checkbox("Hide Record 12+", &HideRecord);

ImGui::Spacing();
ImGui::Separator();
ImGui::Spacing();

ImGui::Text("Hide / show menu");
const char* menuOptions[] = { "Volume UP", "Volume DOWN", "Double Click", "Popup" };

ImGui::SetNextItemWidth(-1); 
if (ImGui::BeginCombo("##MenuControlCombo", menuOptions[OpenedMenus]))
{
    for (int n = 0; n < IM_ARRAYSIZE(menuOptions); n++)
    {
        bool is_selected = (OpenedMenus == n);
        if (ImGui::Selectable(menuOptions[n], is_selected))
        {
            OpenedMenus = n;
        }
        if (is_selected) ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
}

ImGui::Spacing(); ImGui::Spacing();


if (ImGui::Button(languages == 1 ? "Сохранить конфиг" : "Save Config", bigBtnSize)) 
{
    NotifyInfo(languages == 1 ? "Сохранение конфигурации..." : "Saving configuration...");
    if (saveConfig())
        NotifySuccess(languages == 1 ? "Конфигурация сохранена!" : "Configuration saved!");
    else
        NotifyError(languages == 1 ? "Ошибка сохранения!" : "Save failed!");
}
ImGui::Spacing();

if (ImGui::Button(languages == 1 ? "Загрузить конфиг" : "Load Config", bigBtnSize))
{
    NotifyInfo(languages == 1 ? "Загрузка конфигурации..." : "Loading configuration...");
    if (loadConfig())
        NotifySuccess(languages == 1 ? "Конфигурация загружена!" : "Configuration loaded!");
    else
        NotifyError(languages == 1 ? "Ошибка загрузки!" : "Load failed!");
}
ImGui::Spacing();

if (ImGui::Button("Check ban reason", bigBtnSize))
{

}
ImGui::Spacing();

if (ImGui::Button("Reset guest, logout id", bigBtnSize))
{

}}
/// END MENU
}
}
}
ImGui::RenderNotifications();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return orig_eglSwapBuffers(dpy, surface);
}

int (*original_AInputQueue_getEvent)(AInputQueue*, AInputEvent**);

int hooked_AInputQueue_getEvent(AInputQueue* queue, AInputEvent** event) {
    int result = original_AInputQueue_getEvent(queue, event);
    if (result >= 0 && *event) {
        int32_t type = AInputEvent_getType(*event);
        if (type == AINPUT_EVENT_TYPE_MOTION) {
            int32_t action = AMotionEvent_getAction(*event) & AMOTION_EVENT_ACTION_MASK;
            int32_t pointerIndex = (AMotionEvent_getAction(*event) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
            float rawX = AMotionEvent_getX(*event, pointerIndex);
            float rawY = AMotionEvent_getY(*event, pointerIndex);
            float scaledX = (rawX * glWidth) / (float)screenWidth;
            float scaledY = (rawY * glHeight) / (float)screenHeight;
            ImGuiIO& io = ImGui::GetIO();
            switch (action) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                    io.MousePos = ImVec2(scaledX, scaledY);
                    io.MouseDown[0] = true;
                    break;
                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_POINTER_UP:
                    io.MousePos = ImVec2(scaledX, scaledY);
                    io.MouseDown[0] = false;
                    break;
                case AMOTION_EVENT_ACTION_MOVE:
                    io.MousePos = ImVec2(scaledX, scaledY);
                    break;
            }
        }
    }
    return result;
}



void Hook(void *target, void *replace, void **backup) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    mprotect((void *)((uintptr_t)target - ((uintptr_t)target % page_size) - page_size), (size_t)size, PROT_EXEC | PROT_READ | PROT_WRITE);
    DobbyHook(target, replace, backup);
}

void *fetch_game_data(void *) {
    while (true) {
        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;
        auto GWorld = GetWorld();
        if (GWorld) {
            if (GWorld->PersistentLevel) {
                std::vector<AActor *> Actors = GetNecessaryActors();
                {
                    std::lock_guard<std::mutex> lock(actors_mutex);
                    NecessaryActors = Actors;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}

bool UpdateClothSkin(UCharacterAvatarComponent2 *avatar) {
if (!Data::localPlayer)
return false;
if (!Data::localPlayer->AvatarComponent2)
return false;
if (avatar != Data::localPlayer->AvatarComponent2)
return false;
FNetAvatarSyncData NetAvatarComp = *(FNetAvatarSyncData *)((uintptr_t)avatar + Data::Offset::NetAvatarSyncData);
  auto slot = NetAvatarComp.SlotSyncData;
for (int i = 0; i < slot.Num(); i++) {
auto& id = slot[i].ItemId;
auto sl = slot[i].SlotID;

if(sl == 1 && skin.cloth->FACE > 0) //Face 3
{
id = skin.cloth->FACE;
}
if(sl == 2 && skin.cloth->HAT > 0) //hat 8
{
id = skin.cloth->HAT;
}
if(sl == 3 && skin.cloth->MASK > 0)
{ 
 id = skin.cloth->MASK;
}
if(sl == 5 && skin.cloth->SHIRT > 0) // cloth 5
{
id = skin.cloth->SHIRT;
}
if(sl == 10 && skin.cloth->GLOVES > 0) // Gloves 10
{
id = skin.cloth->GLOVES;
}
if(sl == 6 && skin.cloth->PANT > 0) //pant 6
{
id = skin.cloth->PANT;
}
if(sl == 7 && skin.cloth->SHOE > 0) //shoe 7
{
id = skin.cloth->SHOE;
}
switch (id) {
case  502004:
case  502001:
case  502110:
case  502107:
case  502104:
if(sl == 9 && id > 0 && skin.cloth->HELMET1 > 0) //helmet 
{
  id = skin.cloth->HELMET1;
} break; }
switch (id) {
case 502005:
case 502002:
case 502111:
case 502108:
case 502105:
if(sl == 9 && id > 0 && skin.cloth->HELMET2 > 0) //helmet
{
 id = skin.cloth->HELMET2;
} break; }
switch (id) {
case 502106:
case 502109:
case 502112:
case 502003:
if(sl == 9 && id > 0 && skin.cloth->HELMET3 > 0) //helmet
{
  id = skin.cloth->HELMET3;
} break; }
switch (id) {
case 501001:
case 501004:
case 501007:
case 501010:
case 501101:
case 501104:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK1 > 0) //backpack
{
  id = skin.cloth->BACKPACK1;
} break; }
switch (id) {
case  501002:
case  501005:
case  501008:
case  501011:
case  501102:
case  501105:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK2 > 0) //backpack
{
   id = skin.cloth->BACKPACK2;
} break; }
switch (id) {
case 501006:
case 501003:
case 501009:
case 501012:
case 501015:
case 501106:
case 501103:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK3 > 0) //backpack
{
  id = skin.cloth->BACKPACK3;
} break; }
if(sl == 11 && id > 0 && skin.cloth->PARACHUTE > 0) //para
{
id = skin.cloth->PARACHUTE;
}
if(sl == 15 && skin.cloth->GLIDER > 0) //glide
{
id = skin.cloth->GLIDER;
}
   }
return true;
}

bool UpdateClothSkinLobby(UCharacterAvatarComponent2 *avatar)
{
FNetAvatarSyncData NetAvatarComp = *(FNetAvatarSyncData *)((uintptr_t)avatar + Data::Offset::NetAvatarSyncData);
  auto slot = NetAvatarComp.SlotSyncData;
  for (int i = 0; i < slot.Num(); i++)
{
auto& id = slot[i].ItemId;
auto sl = slot[i].SlotID;
  
if(sl == 1 && skin.cloth->FACE > 0) //Face 3
{
id = skin.cloth->FACE;
}
if(sl == 2 && skin.cloth->HAT > 0) //hat 8
{
id = skin.cloth->HAT;
}
if(sl == 3 && skin.cloth->MASK > 0)
{ 
   id = skin.cloth->MASK;
}
if(sl == 5 && skin.cloth->SHIRT > 0) // cloth
{
id = skin.cloth->SHIRT;
}
if(sl == 10 && skin.cloth->GLOVES > 0) // Gloves
{
id = skin.cloth->GLOVES;
}
if(sl == 6 && skin.cloth->PANT > 0) //pant
{
id = skin.cloth->PANT;
}
if(sl == 7 && skin.cloth->SHOE > 0) //shoe
{
id = skin.cloth->SHOE;
}
switch (id) {
case  502004:
case  502001:
case  502110:
case  502107:
case  502104:
if(sl == 9 && id > 0 && skin.cloth->HELMET1 > 0) //helmet
{
  id = skin.cloth->HELMET1;
} break; }
switch (id) {
case 502005:
case 502002:
case 502111:
case 502108:
case 502105:
if(sl == 9 && id > 0 && skin.cloth->HELMET2 > 0) //helmet
{
 id = skin.cloth->HELMET2;
} break; }
switch (id) {
case 502106:
case 502109:
case 502112:
case 502003:
if(sl == 9 && id > 0 && skin.cloth->HELMET3 > 0) //helmet
{
  id = skin.cloth->HELMET3;
} break; }
switch (id) {
case 501001:
case 501004:
case 501007:
case 501010:
case 501101:
case 501104:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK1 > 0) //backpack
{
  id = skin.cloth->BACKPACK1;
} break; }
switch (id) {
case  501002:
case  501005:
case  501008:
case  501011:
case  501102:
case  501105:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK2 > 0) //backpack
{
   id = skin.cloth->BACKPACK2;
} break; }
switch (id) {
case 501006:
case 501003:
case 501009:
case 501012:
case 501015:
case 501106:
case 501103:
if(sl == 8 && id > 0 && skin.cloth->BACKPACK3 > 0) //backpack
{
  id = skin.cloth->BACKPACK3;
} break; }
if(sl == 11 && id > 0 && skin.cloth->PARACHUTE > 0) //para
{
id = skin.cloth->PARACHUTE;
}
if(sl == 15 && skin.cloth->GLIDER > 0) //glide
{
id = skin.cloth->GLIDER;
}
   }
   
return true;
}

#include <string>

void* (*oProcessEvent)(UObject* pObj, UFunction* pFunc, void* pArgs) = nullptr;

void ChangeGunSkin(ASTExtraWeapon* gun, UObject* localPlayer = nullptr)
{
    if (!gun) return;

    if (!localPlayer || gun->Owner == localPlayer || gun->GetInstigator() == localPlayer)  
    {  
        int id = gun->GetWeaponID();  
        if (id <= 0) return;  

        int newID = GetWeap(id);  
        if (newID > 0)  
        {  
            auto fg = GetFullWeapon(newID);  
            fg.ChangeSkin(gun);  
        }  
    }
}

void* hkProcessEvent(UObject* a1, UFunction* a, void* b) {
    if (!a1 || !a) {
        return oProcessEvent ? oProcessEvent(a1, a, b) : nullptr;
    }

    std::string fnc = a->GetFullName();
    if (fnc.empty()) {
        return oProcessEvent(a1, a, b);
    }

    if (ReceiveDrawHUD_Index == -1 && fnc.find("Function Engine.HUD.ReceiveDrawHUD") != std::string::npos) {
        ReceiveDrawHUD_Index = a->InternalIndex;
    }

    if (OnRep_AvatarMeshChanged_Index == -1 && fnc.find("ShadowTrackerExtra.STExtraWeapon.OnRep_AvatarMeshChanged") != std::string::npos) {
        OnRep_AvatarMeshChanged_Index = a->InternalIndex;
    }

    if (OnRep_BodySlotStateChanged_Index == -1 && fnc.find("ShadowTrackerExtra.CharacterAvatarComponent2.OnRep_BodySlotStateChanged") != std::string::npos) {
        OnRep_BodySlotStateChanged_Index = a->InternalIndex;
    }

    if (CreateWeaponAndChangeSkin_Index == -1 && fnc.find("CreateWeaponAndSkin") != std::string::npos) {
        CreateWeaponAndChangeSkin_Index = a->InternalIndex;
    }

    if (skin.bEnable) {

        if (skin.bGunSkin && (a->InternalIndex == OnRep_AvatarMeshChanged_Index || fnc.find("OnRep_AvatarMeshChanged") != std::string::npos)) {
            if (a1->IsA(ASTExtraWeapon::StaticClass())) {
                auto gun = reinterpret_cast<ASTExtraWeapon*>(a1);
                if (gun) {
                    ChangeGunSkin(gun);
                }
            }
        }

        if (skin.bGunSkin && a->InternalIndex == CreateWeaponAndChangeSkin_Index) {
            if (b) {
                auto params = reinterpret_cast<ULobbyWeaponManagerComponent_CreateWeaponAndSkin_Params*>(b);
                if (params) {
                    params->bSync = false;
                    params->bUse = true;
                    int g_WeaponID = params->WeaponSkinID;
                    DWORD gun_val = GetWeap(g_WeaponID);
                    if (gun_val > 0) {
                        params->WeaponSkinID = gun_val;
                    }
                }
            }
            return oProcessEvent(a1, a, b);
        }

        if (skin.bClothSkin && (a->InternalIndex == OnRep_BodySlotStateChanged_Index || 
                               fnc.find("OnRep_BodySlotStateChanged") != std::string::npos || 
                               fnc.find("GetServerForceHideState") != std::string::npos)) {
            if (a1->IsA(UCharacterAvatarComponent2::StaticClass())) {
                auto avatar = reinterpret_cast<UCharacterAvatarComponent2*>(a1);
                if (avatar) {
                    UpdateClothSkin(avatar);
                    UpdateClothSkinLobby(avatar);
                }
            }
            return oProcessEvent(a1, a, b);
        }

        if (!Data::localController && skin.bVehicleSkin && fnc.find("VehicleAvatarComponent_BP.VehicleAvatarComponent_BP_C.GetItemAvatarHandle") != std::string::npos) {
            if (b) {
                auto PARAMS = reinterpret_cast<UVehicleAvatarComponent_GetItemAvatarHandle_Params*>(b);
                if (PARAMS) {
                    int neww = GetVehSkinModded(PARAMS->ItemId);
                    if (neww > 0) {
                        PARAMS->ItemId = neww;
                    }
                }
            }
            return oProcessEvent(a1, a, b);
        }
    }

    return oProcessEvent(a1, a, b);
}


#define HOOK(addr, ptr, orig) hook((void *)(addr), (void *)ptr, (void **)&orig)

//=======================================   Bypass Start   ===============================================//
//#include "hook.h"
size_t libanogsSize = 0;
size_t libUE4Size = 0;

size_t LibrarySize(const char* libraryName) {
    FILE* mapsFile = fopen("/proc/self/maps", "r");
    if (!mapsFile) return 0;

    char line[512];
    uintptr_t startAddr = 0, endAddr = 0;
    bool found = false;

    while (fgets(line, sizeof(line), mapsFile)) {
        if (strstr(line, libraryName)) {
            uintptr_t tmpStart = 0, tmpEnd = 0;
            if (sscanf(line, "%lx-%lx", &tmpStart, &tmpEnd) == 2) {
                if (!found) { startAddr = tmpStart; found = true; }
                endAddr = tmpEnd;
            }
        } else if (found) break;
    }

    fclose(mapsFile);
    return (found && endAddr > startAddr) ? (size_t)(endAddr - startAddr) : 0;
}

void Init() {
    libUE4Size = LibrarySize("libUE4.so");
    libanogsSize = LibrarySize("libanogs.so");
}
//==================================   Lua Offset  ===============================
void Main_Lua()
{
    while (!UE4) 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
*(uintptr_t *)&Lua::luaL_loadbufferx_Ptr =  UE4 + (0xB52BAE0);
*(uintptr_t *)&Lua::lua_pcall_Ptr =  UE4 + (0xB508028);
*(uintptr_t *)&Lua::sub_BA003F8_Ptr =  UE4 + (0xC21B750);
*(uintptr_t *)&Lua::lua_tostring_Ptr =  UE4 + (0xB506448);

    Lua::Initialize();
}
__attribute__((constructor)) void library_constructor()
{
    std::thread(Main_Lua).detach();
}
//======================================  Main Egl  ===========================
void *main_thread(void *) {    
    //Main_Thread2();
    UE4 = GetBaseAddress("libUE4.so");
    while (!UE4) {
        UE4 = GetBaseAddress("libUE4.so");
        sleep(1);
    }
    ANORT = GetBaseAddress("libanort.so");
    while (!ANORT) {
        ANORT = GetBaseAddress("libanort.so");
        sleep(1);
    }
    while (!g_App) {
        g_App = *(android_app**)(UE4 + GNativeAndroidApp_Offset);
        usleep(200 * 1000);
    }
    UObject::GUObjectArray = (FUObjectArray*)(UE4 + GUObject_Offset);
    do {
        FName::GNames = GetGNames();
        usleep(200 * 1000);
    } while (!FName::GNames);
    HOOK(UE4 + oxorany(0xA5D3514), hPostRender, oPostRender);
    HOOK(UE4 + oxorany(0x8BAC0A8), hkProcessEvent, oProcessEvent);
    DobbyHook((void *)DobbySymbolResolver("/system/lib64/libandroid.so", "AInputQueue_getEvent"), (void *)hooked_AInputQueue_getEvent, (void **)&original_AInputQueue_getEvent);
    DobbyHook((void *)DobbySymbolResolver("/system/lib/libUE4.so", "eglSwapBuffers"), (void *)_eglSwapBuffers, (void **)&orig_eglSwapBuffers);
    pthread_t t;
    pthread_create(&t, nullptr, fetch_game_data, nullptr);
    return nullptr;
}


__attribute__((constructor))
void _init() {
    pthread_t t;
    pthread_create(&t, nullptr, main_thread, nullptr);
}