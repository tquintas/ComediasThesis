---@diagnostic disable: undefined-global
local lib_path = reaper.GetExtState("Lokasenna_GUI", "lib_path_v2")
loadfile(lib_path .. "Core.lua")()
dofile(reaper.GetResourcePath().."/UserPlugins/ultraschall_api.lua")

GUI.req("Classes/Class - Button.lua")()

GUI.name = "Reloading..."
GUI.x, GUI.y, GUI.w, GUI.h = 0,0,220,310

GUI.anchor, GUI.corner = "mouse", "C"

Vol = 1

function Fade(track, i)
    reaper.SetMediaTrackInfo_Value(track, "D_VOL", Vol)
    Vol = Vol - 0.01
    if Vol < 0 then
        reaper.TrackFX_Delete(track, 0)
        reaper.TrackFX_AddByName(track, "bitklavier", false, -1000)
        reaper.TrackFX_SetPreset(track, 0, i)
        reaper.SetMediaTrackInfo_Value(track, "D_VOL", 1)
        return
    end
    ultraschall.Defer((function() Fade(track, i) end), "track_fade", 2, 0.05)
end

local function Reload(i)
    Vol = 1
    local tr = reaper.GetTrack(0, i)
    if tr then
        Fade(tr, i)
    end
end

local function FXSetup()
    local tr1 = reaper.GetTrack(0, 0)
    if tr1 then
        reaper.ShowMessageBox("Track already created!", "Setup failed...", 0)
        return
    end
    reaper.InsertTrackAtIndex(0, true)
    local tr = reaper.GetTrack(0, 0)
    reaper.TrackFX_AddByName(tr, "bitklavier", false, 1)
    reaper.ShowMessageBox("Create 5 presets.\nFor each N from 1 to 5:\n - Select XGalleryN;\n - Go to Preferences and add the bitSamples folder to the Sample search paths;\n - Select the XSynth sound;\n - Save the preset as N.", "FX Setup", 0)
end

local function Setup()
    local tr1 = reaper.GetTrack(0, 0)
    if tr1 then
        reaper.ShowMessageBox("Track already created!", "Setup failed...", 0)
        return
    end
    reaper.InsertTrackAtIndex(0, true)
    local folder = reaper.GetTrack(0, 0)
    reaper.GetSetMediaTrackInfo_String(folder, "P_NAME", "bitklavier_MIDI", true)
    reaper.SetMediaTrackInfo_Value(folder, "I_FOLDERDEPTH", 1)
    reaper.SetMediaTrackInfo_Value(folder, "B_MAINSEND", 0)
    reaper.TrackFX_AddByName(folder, "masterlimiter", false, 1)

    for i = 1, 5 do
        reaper.InsertTrackAtIndex(i, true)
        local tr = reaper.GetTrack(0, i)
        reaper.GetSetMediaTrackInfo_String(tr, "P_NAME", ""..i, true)
        reaper.SetMediaTrackInfo_Value(tr, "I_RECARM", 1)
        reaper.SetMediaTrackInfo_Value(tr, "I_RECINPUT", 6112)
        reaper.TrackFX_AddByName(tr, "bitklavier", false, 1)
        reaper.TrackFX_SetPreset(tr, 0, i)
        reaper.TrackFX_AddByName(tr, "masterlimiter", false, 3)
        if i == 5 then reaper.SetMediaTrackInfo_Value(tr, "I_FOLDERDEPTH", -1) end
    end

    reaper.InsertTrackAtIndex(6, true)
    local folder2 = reaper.GetTrack(0, 6)
    reaper.GetSetMediaTrackInfo_String(folder2, "P_NAME", "bitklavier_Audio", true)
    reaper.SetMediaTrackInfo_Value(folder2, "I_FOLDERDEPTH", 1)
    reaper.TrackFX_AddByName(folder2, "masterlimiter", false, 1)

    for i = 7, 11 do
        reaper.InsertTrackAtIndex(i, true)
        local tr = reaper.GetTrack(0, i)
        reaper.GetSetMediaTrackInfo_String(tr, "P_NAME", ""..(i-6), true)
        reaper.SetMediaTrackInfo_Value(tr, "I_RECARM", 1)
        reaper.SetMediaTrackInfo_Value(tr, "I_RECMODE", 3)
        reaper.CreateTrackSend(reaper.GetTrack(0, i-6), tr)
        reaper.TrackFX_AddByName(tr, "masterlimiter", false, 1)
    end
end

NoKeys = false
function ShortcutBtns()
    local key = GUI.char
    local cmd = GUI.mouse.cap & 4 == 4
    local key_now = (key ~= 0)
    if cmd and NoKeys and key_now then
        if key == 48 then Setup()
        elseif key > 48 and key < 54 then Reload(key - 48) end
    end
    NoKeys = (key == 0)
end

GUI.New("setup_btn", "Button", {
    z = 11,
    x = 10,
    y = 10,
    w = 200,
    h = 30,
    caption = "FX Setup",
    font = 3,
    col_txt = "txt",
    col_fill = "elm_frame",
    func = FXSetup
})

GUI.New("build_btn", "Button", {
    z = 11,
    x = 10,
    y = 42,
    w = 200,
    h = 30,
    caption = "Build tracks",
    font = 3,
    col_txt = "txt",
    col_fill = "elm_frame",
    func = Setup
})

for i = 1,5 do
    GUI.New(i.."_btn", "Button", {
        z = 11,
        x = 10,
        y = 82 + (i-1)*32,
        w = 200,
        h = 30,
        caption = "Reload channel "..i,
        font = 3,
        col_txt = "txt",
        col_fill = "elm_frame",
        func = (function() Reload(i) end)
    })
end

GUI.func = ShortcutBtns
GUI.freq = 0.01
GUI.exit = (function ()
    GUI.func = nil  
end)
GUI.Init()
GUI.Main()
