#ifndef ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H
#define ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H

#include "geometry_generator.h"
#include "simulator.h"
#include "engine.h"
#include "simulation_object.h"
#include "ui_manager.h"
#include "dynamometer.h"
#include "oscilloscope.h"
#include "audio_buffer.h"
#include "convolution_filter.h"
#include "shaders.h"
#include "engine_view.h"
#include "right_gauge_cluster.h"
#include "cylinder_temperature_gauge.h"
#include "synthesizer.h"
#include "oscilloscope_cluster.h"
#include "performance_cluster.h"
#include "load_simulation_cluster.h"
#include "mixer_cluster.h"
#include "info_cluster.h"

#include "delta.h"
#include "dtv.h"

#include <vector>

#include "./loader/loader.h"

#include <filesystem>

#include "./lua/lua.hpp"
#include "./loader/logger.h"

class EngineSimApplication {
    private:
        static std::string s_buildVersion;
        static std::string s_modLoaderVersion;
        static int s_modAmount;

    public:
        EngineSimApplication();
        virtual ~EngineSimApplication();
        static EngineSimApplication* instance;

        static std::string getBuildVersion() { return s_buildVersion; }
        static std::string getModLoaderVersion() { return s_modLoaderVersion; }
        static std::string getModAmount() { return std::to_string(s_modAmount); }

        void initialize(void *instance, ysContextObject::DeviceAPI api);
        void run();
        void destroy();

        void drawGenerated(
                const GeometryGenerator::GeometryIndices &indices,
                int layer = 0);
        void drawGeneratedUi(
                const GeometryGenerator::GeometryIndices &indices,
                int layer = 0);
        void drawGenerated(
                const GeometryGenerator::GeometryIndices &indices,
                int layer,
                dbasic::StageEnableFlags flags);
        GeometryGenerator *getGeometryGenerator() { return &m_geometryGenerator; }

        Shaders *getShaders() { return &m_shaders; }
        dbasic::TextRenderer *getTextRenderer() { return &m_textRenderer; }

        void createObjects(Engine *engine);
        dbasic::DeltaEngine *getEngine() { return &m_engine; }

        float pixelsToUnits(float pixels) const;
        float unitsToPixels(float units) const;

        ysVector getBackgroundColor() const { return m_background; }
        ysVector getHightlight1Color() const { return m_highlight1; }
        ysVector getWhite() const { return ysMath::Constants::One; }
        ysVector getPink() const { return m_pink; }
        ysVector getGreen() const { return m_green; }
        ysVector getYellow() const { return m_yellow; }
        ysVector getRed() const { return m_red; }
        ysVector getOrange() const { return m_orange; }
        ysVector getBlue() const { return m_blue; }

        void SetPink(double R, double G, double B);
        void SetGreen(double R, double G, double B);
        void SetYellow(double R, double G, double B);
        void SetRed(double R, double G, double B);
        void SetOrange(double R, double G, double B);
        void SetBlue(double R, double G, double B);

        const SimulationObject::ViewParameters &getViewParameters() const;
        void setViewLayer(int view) { m_viewParameters.Layer0 = view; }

        dbasic::AssetManager *getAssetManager() { return &m_assetManager; }

        int getScreenWidth() const { return m_screenWidth; }
        int getScreenHeight() const { return m_screenHeight; }

        Simulator *getSimulator() { return &m_simulator; }
        InfoCluster *getInfoCluster() { return m_infoCluster; }

        std::string UNIT_TYPE_TORQUE = "imperial";
        std::string UNIT_TYPE_SPEED = "imperial";
        std::string UNIT_TYPE_AIRFLOW = "imperial";
        std::string UNIT_TYPE_PRESSURE = "imperial";

    protected:
        void renderScene();

    protected:
        virtual void initialize();
        virtual void process(float dt);
        virtual void render();

        // LUA

        // 243, 148, 190
        double PinkR = 243;
        double PinkG = 148;
        double PinkB = 190;

        // 189, 216, 105
        double GreenR = 189;
        double GreenG = 216;
        double GreenB = 105;

        // 253, 189, 46
        double YellowR = 253;
        double YellowG = 189;
        double YellowB = 46;

        // 238, 68, 69
        double RedR = 238;
        double RedG = 68;
        double RedB = 69;

        // 244, 128, 42
        double OrangeR = 244;
        double OrangeG = 128;
        double OrangeB = 42;

        // 119, 206, 224
        double BlueR = 119;
        double BlueG = 206;
        double BlueB = 224;

        // LUA STUFF
        void loadLua(std::string luaPath);
        void luaLoadConfig(std::string luaPath);
        void unloadLua();
        void luaFail(std::string error);
        lua_State* L;

        /*
        int luaSetPink(lua_State* lua);
        int luaSetGreen(lua_State* lua);
        int luaSetYellow(lua_State* lua);
        int luaSetRed(lua_State* lua);
        int luaSetOrange(lua_State* lua);
        int luaSetBlue(lua_State* lua);
        */

        void luaSetupVars();
        void luaSetInVar(ysKey::Code code, std::string* name);

        void luaSetupEngineVars(bool start);
        void luaSetVar(std::string name, std::string value);

        void luaGetEngineVars();
        void luaGetUiVars();
        //void luaSetUiVar(std::string color);
        std::string luaGetVar(std::string name);

        // LUA FUNCTIONS
        void luaProcess(float dt);

        void luaStart();

        float m_displayHeight;
        int m_gameWindowHeight;
        int m_screenWidth;
        int m_screenHeight;

        dbasic::ShaderSet m_shaderSet;
        Shaders m_shaders;

    public:

        dbasic::DeltaEngine m_engine;
        dbasic::AssetManager m_assetManager;

        std::string m_assetPath;

        ysRenderTarget *m_mainRenderTarget;
        ysGPUBuffer *m_geometryVertexBuffer;
        ysGPUBuffer *m_geometryIndexBuffer;

        GeometryGenerator m_geometryGenerator;
        dbasic::TextRenderer m_textRenderer;

        std::vector<SimulationObject *> m_objects;
        Engine *m_iceEngine;
        Simulator m_simulator;
        double m_dynoSpeed;
        double m_torque;

        UiManager m_uiManager;
        EngineView *m_engineView;
        RightGaugeCluster *m_rightGaugeCluster;
        OscilloscopeCluster *m_oscCluster;
        CylinderTemperatureGauge *m_temperatureGauge;
        PerformanceCluster *m_performanceCluster;
        LoadSimulationCluster *m_loadSimulationCluster;
        MixerCluster *m_mixerCluster;
        InfoCluster *m_infoCluster;
        SimulationObject::ViewParameters m_viewParameters;

        bool m_paused;

    protected:
        void startRecording();
        void updateScreenSizeStability();
        bool readyToRecord();
        void stopRecording();
        void recordFrame();
        bool isRecording() const { return m_recording; }

        static constexpr int ScreenResolutionHistoryLength = 5;
        int m_screenResolution[ScreenResolutionHistoryLength][2];
        int m_screenResolutionIndex;
        bool m_recording;

        ysVector m_background;
        ysVector m_foreground;
        ysVector m_shadow;
        ysVector m_highlight1;
        ysVector m_highlight2;

        ysVector m_pink;
        ysVector m_orange;
        ysVector m_yellow;
        ysVector m_red;
        ysVector m_green;
        ysVector m_blue;

        ysAudioBuffer *m_outputAudioBuffer;
        AudioBuffer m_audioBuffer;
        ysAudioSource *m_audioSource;

        int m_oscillatorSampleOffset;
        int m_screen;

#ifdef ATG_ENGINE_SIM_VIDEO_CAPTURE
        atg_dtv::Encoder m_encoder;
#endif /* ATG_ENGINE_SIM_VIDEO_CAPTURE */
};

#endif /* ATG_ENGINE_SIM_ENGINE_SIM_APPLICATION_H */
