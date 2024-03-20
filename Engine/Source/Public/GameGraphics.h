#pragma once
#include <SDL2/SDL_image.h>
#include "Graphics/Color.h"
#include "Nodes/Visual.h"
#include "Game.h"

struct Color;
enum VisualBlendingMode;

class Graphics
{
    friend class Game;
    friend class Visual;

private:
    struct VisualsInRenderLayer
    {
    public:
        int index;
        std::vector<Visual*> visualsInZOrder;
    };

public:
    enum WindowFlags : unsigned int
    {
        /// <summary>No Masks.</summary>
        None = 0u,
        /// <summary>Window is fullscreen.</summary>
        Fullscreen = 1u << 0,
        /// <summary>Window usable with OpenGL context.</summary>
        OpenGL = 1u << 1,
        /// <summary>Window is visible.</summary>
        Shown = 1u << 2,
        /// <summary>Window isn't visible.</summary>
        Hidden = 1u << 3,
        /// <summary>No window border or tab.</summary>
        Borderless = 1u << 4,
        /// <summary>Window can be resized.</summary>
        Resizable = 1u << 5,
        /// <summary>Window is minimized.</summary>
        Minimized = 1u << 6,
        /// <summary>Window is maximized.</summary>
        Maximized = 1u << 7,
        /// <summary>Mouse input has been grabbed.</summary>
        MouseGrabbed = 1u << 8,
        /// <summary>Window has input focused.</summary>
        InputFocus = 1u << 9,
        /// <summary>Window has mouse focused.</summary>
        MouseFocus = 1u << 10,
        FullscreenDesktop = (Fullscreen | (1u << 12)),
        /*
        /// <summary>Window was not created by this.</summary>
        Foreign = 1u << 11,            *< window not created by SDL
        /// <summary>Window should be created in high-DPI mode if supported. On macOS NSHighResolutionCapable must be set true in the application's Info.plist for this to have any effect.</summary>
        AllowHighDPI = 1u << 13,
        */
        /// <summary>Window has mouse captured. (unrelated to MOUSE_GRABBED)</summary>
        MouseCapture = 1u << 14,
        /// <summary>Window is always on top of everything else.</summary>
        AlwaysOnTop = 1u << 15,
        /// <summary>Window is seen on the taskbar.</summary>
        NoTaskbar = 1u << 16,
        /// <summary>Window is treated like a utility window.</summary>
        IsUtility = 1u << 17,
        /// <summary>Window is is treated like a tooltip.</summary>
        IsTooltip = 1u << 18,
        /// <summary>Window is is treated like a popup.</summary>
        PopUp = 1u << 19,
        /// <summary>Keyboard input has been grabbed.</summary>
        KeyboardCaptured = 1u << 20,
        /*
        Vulkan = 1u << 21,
        Metal = 1u << 22,
        */
    };

    struct RenderLayerFlags
    {
    public:
        int renderLayerIndex;
        Color color;
        VisualBlendingMode blendingMode;

        constexpr RenderLayerFlags(int renderLayerIndex, Color color = COLOR_WHITE, VisualBlendingMode blendingMode = (VisualBlendingMode)0u) :
            renderLayerIndex(renderLayerIndex),
            color(color),
            blendingMode(blendingMode)
        { }
    };

public:
    Color backgroundColor;

private:
    SDL_Texture* _renderBuffer;
    Vector2I _renderBufferSize;
	SDL_Renderer* _renderer;
    SDL_Window* _window;
    std::vector<VisualsInRenderLayer> _visualsInRenderLayers;
    std::vector<RenderLayerFlags> _renderLayerFlags;

public:
    Graphics(const char* title, int posX, int posY, int sizeX, int sizeY, unsigned int flags) noexcept;
    ~Graphics() noexcept;

    static constexpr int CenteredWindowFlag(int display = 0) { return SDL_WINDOWPOS_CENTERED_DISPLAY(display); }
    static constexpr int AutoPosWindowFlag(int display = 0) { return SDL_WINDOWPOS_UNDEFINED_DISPLAY(display); }

private:
    void DoRender();
};