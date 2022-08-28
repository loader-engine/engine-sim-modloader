#ifndef ATG_ENGINE_SIM_LOAD_SIMULATION_CLUSTER_H
#define ATG_ENGINE_SIM_LOAD_SIMULATION_CLUSTER_H

#include "ui_element.h"

#include "simulator.h"
#include "labeled_gauge.h"

class LoadSimulationCluster : public UiElement {
    public:
        LoadSimulationCluster();
        virtual ~LoadSimulationCluster();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();
<<<<<<< HEAD
        void setUnits();
=======
        void   setUnits();
        double getPower(double torque);
>>>>>>> 6c8f1480d74aeef8c17a78ee6427407f2a8d02e5

        void setSimulator(Simulator *simulator) { m_simulator = simulator; }

    protected:
        void drawCurrentGear(const Bounds &bounds);
        void drawClutchPressureGauge(const Bounds &bounds);
        void drawSystemStatus(const Bounds &bounds);
        void updateHpAndTorque(float dt);

        float m_systemStatusLights[4];
        LabeledGauge *m_dynoSpeedGauge;
        LabeledGauge *m_torqueGauge;
        LabeledGauge *m_hpGauge;
        LabeledGauge *m_clutchPressureGauge;

        double m_filteredHorsepower;
        double m_filteredTorque;

        double m_peakHorsepowerRpm;
        double m_peakHorsepower;
        double m_peakTorqueRpm;
        double m_peakTorque;
        
        std::string m_powerUnits;
        std::string m_torqueUnits;

        Simulator *m_simulator;
};

#endif /* ATG_ENGINE_SIM_LOAD_SIMULATION_CLUSTER_H */
