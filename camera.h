#include <numbers> // Required for std::numbers::pi (Version 1)

// NoxarTM Version 1: Use this if you're obtaining FOV from the Player Controller.
// Note: Offsets for location and rotation were manually dumped by NoxarTM. 
// These values might need updating in future patches!
Camera get_view_point_noxar_player_controller()
{
    Camera view_point{};
    // Manually dumped offsets by NoxarTM. Verify in the next update!
    uintptr_t location_pointer = read<uintptr_t>(cache::uworld + 0x128); 
    uintptr_t rotation_pointer = read<uintptr_t>(cache::uworld + 0x138); 
    FNRot fnrot{};
    fnrot.a = read<double>(rotation_pointer);
    fnrot.b = read<double>(rotation_pointer + 0x20);
    fnrot.c = read<double>(rotation_pointer + 0x1D0);
    
    view_point.location = read<Vector3>(location_pointer);
    view_point.rotation.x = asin(fnrot.c) * (180.0 / M_PI);
    view_point.rotation.y = ((atan2(-fnrot.a, fnrot.b) * (180.0 / M_PI)) * -1);
    
    // Retrieve FOV from Player Controller, doubled then converted to degrees using std::numbers::pi.
    auto fov_radians = read<float>(cache::player_controller + 0x3AC) * 2;
    view_point.fov = fov_radians * 180.0f / std::numbers::pi;
    
    return view_point;
}

// NoxarTM Version 2: Use this if you're obtaining FOV from the LocalPlayer.
// Note: Offsets were manually dumped by NoxarTM and may change with updates.
Camera get_view_point_noxar_local_player()
{
    Camera view_point{};
    // Manually dumped offsets by NoxarTM. Always check for updates!
    uintptr_t location_pointer = read<uintptr_t>(cache::uworld + 0x128); 
    uintptr_t rotation_pointer = read<uintptr_t>(cache::uworld + 0x138); 
    FNRot fnrot{};
    fnrot.a = read<double>(rotation_pointer);
    fnrot.b = read<double>(rotation_pointer + 0x20);
    fnrot.c = read<double>(rotation_pointer + 0x1D0);
    
    view_point.location = read<Vector3>(location_pointer);
    view_point.rotation.x = asin(fnrot.c) * (180.0 / M_PI);
    view_point.rotation.y = ((atan2(-fnrot.a, fnrot.b) * (180.0 / M_PI)) * -1);
    
    // Retrieve FOV directly from the LocalPlayer (offset might be updated in future versions).
    view_point.fov = read<float>(cache::local_player + 0x4AC);
    
    return view_point;
}

// NoxarTM Version 3: Fallback option if the above methods fail.
// Note: Uses the Player Controller's FOV multiplied by 90.0f as a fallback method.
Camera get_view_point_noxar_fallback()
{
    Camera view_point{};
    // Offsets manually dumped by NoxarTM – double-check them if you encounter issues!
    uintptr_t location_pointer = read<uintptr_t>(cache::uworld + 0x128); 
    uintptr_t rotation_pointer = read<uintptr_t>(cache::uworld + 0x138); 
    FNRot fnrot{};
    fnrot.a = read<double>(rotation_pointer);
    fnrot.b = read<double>(rotation_pointer + 0x20);
    fnrot.c = read<double>(rotation_pointer + 0x1D0);
    
    view_point.location = read<Vector3>(location_pointer);
    view_point.rotation.x = asin(fnrot.c) * (180.0 / M_PI);
    view_point.rotation.y = ((atan2(-fnrot.a, fnrot.b) * (180.0 / M_PI)) * -1);
    
    // Fallback: Use Player Controller's FOV multiplied by 90.0f.
    view_point.fov = read<float>(cache::player_controller + 0x3AC) * 90.0f;
    
    return view_point;
}
