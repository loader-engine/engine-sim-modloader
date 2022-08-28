#ifndef ATG_ENGINE_SIM_RIGHT_GAUGE_CLUSTER_H
#define ATG_ENGINE_SIM_RIGHT_GAUGE_CLUSTER_H

#include "ui_element.h"

#include "engine.h"
#include "simulator.h"
#include "gauge.h"
#include "firing_order_display.h"
#include "labeled_gauge.h"
#include "throttle_display.h"
#include "afr_cluster.h"
#include "fuel_cluster.h"

class RightGaugeCluster : public UiElement {
    public:
        RightGaugeCluster();
        virtual ~RightGaugeCluster();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();

<<<<<<< HEAD
        void setEngine(Engine *engine);
        void setUnits();
        double getManifoldPressureWithUnits(double ambientPressure);
=======
        void   setEngine(Engine *engine);
        void   setUnits();
        double getPressureVaccuum(double ambientPressure);
>>>>>>> 6c8f1480d74aeef8c17a78ee6427407f2a8d02e5
        Simulator *m_simulator;

    protected:
        Engine *m_engine;

        void renderTachSpeedCluster(const Bounds &bounds);
        void renderFuelAirCluster(const Bounds &bounds);

        LabeledGauge *m_tachometer;
        LabeledGauge *m_speedometer;
        LabeledGauge *m_manifoldVacuumGauge;
        LabeledGauge *m_intakeCfmGauge;
        LabeledGauge *m_volumetricEffGauge;
        FuelCluster *m_fuelCluster;
        ThrottleDisplay *m_throttleDisplay;
        AfrCluster *m_afrCluster;
        FiringOrderDisplay *m_combusionChamberStatus;
        std::string m_speedUnits;
        std::string m_pressureUnits;
<<<<<<< HEAD
        bool m_isAbsolute;
=======
        bool isAbsolute;
>>>>>>> 6c8f1480d74aeef8c17a78ee6427407f2a8d02e5
};

#endif /* ATG_ENGINE_SIM_GAUGE_CLUSTER_H */
