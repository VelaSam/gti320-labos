#include "ParticleSimApplication.h"
#include "ParticleSimGLCanvas.h"

#include <nanogui/window.h>
#include <nanogui/formhelper.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/graph.h>
#include <nanogui/tabwidget.h>
#include <nanogui/opengl.h>

#include <fstream>
#include <random>
#include <cmath>

using namespace gti320;

namespace
{
    static const float deltaT = 0.01667f;


    /**
     * Crée un système masse-ressort qui simule un tissu suspendu
     */
    static inline void createHangingCloth(ParticleSystem& particleSystem, float k)
    {
        particleSystem.clear();

        const int N = 16;
        const int x_start = 240;
        const int y_start = 80;
        const int dx = 32;
        const int dy = 32;

        int index = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                const int x = x_start + j * dx;
                const int y = y_start + i * dy;

                Particle particle(Vector2f(x, y), Vector2f(0, 0), Vector2f(0, 0), 1.0);
                if (j == 0 && i == (N - 1)) particle.fixed = true;
                if (j == (N - 1) && i == (N - 1)) particle.fixed = true;
                particleSystem.addParticle(particle);

                if (i > 0)
                {
                    Spring s(index - N, index, k, (float)dy);
                    particleSystem.addSpring(s);
                }
                if (j > 0)
                {
                    Spring s(index - 1, index, k, (float)dx);
                    particleSystem.addSpring(s);
                }

                if (i > 0 && j > 0)
                {
                    Spring s(index - N - 1, index, k, std::sqrt((float)dx * dx + (float)dy * dy));
                    particleSystem.addSpring(s);
                }
                ++index;
            }
        }

    }


    /**
     * Crée un système masse-ressort qui simule un grand tissu suspendu
     */
    static inline void createLargeHangingCloth(ParticleSystem& particleSystem, float k)
    {
        particleSystem.clear();

        const int N = 32;
        const int x_start = 240;
        const int y_start = 80;
        const int dx = 16;
        const int dy = 16;

        int index = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                const int x = x_start + j * dx;
                const int y = y_start + i * dy;

                Particle particle(Vector2f(x, y), Vector2f(0, 0), Vector2f(0, 0), 1.0);
                if (j == 0 && i == (N - 1)) particle.fixed = true;
                if (j == (N - 1) && i == (N - 1)) particle.fixed = true;
                particleSystem.addParticle(particle);
                if (i > 0)
                {
                    Spring s(index - N, index, k, (float)dy);
                    particleSystem.addSpring(s);
                }
                if (j > 0)
                {
                    Spring s(index - 1, index, k, (float)dx);
                    particleSystem.addSpring(s);
                }

                if (i > 0 && j > 0)
                {
                    Spring s(index - N - 1, index, k, std::sqrt((float)dx * dx + (float)dy * dy));
                    particleSystem.addSpring(s);
                }
                ++index;
            }
        }

    }

    /**
     * Crée un système masse-ressort qui simule une corde suspendu par ses
     * extrémités.
     */
    static inline void createHangingRope(ParticleSystem& particleSystem, float k)
    {
        particleSystem.clear();

        const int N = 20;
        const int x_start = 200;
        const int dx = 32;

        int index = 0;
        for (int j = 0; j < N; ++j)
        {
            const int x = x_start + j * dx;
            const int y = 480;

            Particle particle(Vector2f(x, y), Vector2f(0, 0), Vector2f(0, 0), 1.0);
            particle.fixed = (index == 0) || (index == N - 1);
            particleSystem.addParticle(particle);
            if (j > 0)
            {
                Spring s(index - 1, index, k, (float)dx);
                particleSystem.addSpring(s);
            }
            ++index;
        }

    }

    /**
     * Crée un système masse-ressort qui  simule une poutre flexible
     */
    static inline void createBeam(ParticleSystem& particleSystem, float k)
    {
        particleSystem.clear();

        const int N = 20;
        const int x_start = 200;
        const int y_start = 400;
        const int dx = 32;
        const int dy = 32;

        int index = 0;
        for (int j = 0; j < N; ++j)
        {
            const int x = x_start + j * dx;

            // Bottom particle
            {
                Particle particle(Vector2f(x, y_start), Vector2f(0, 0), Vector2f(0, 0), 1.0);
                particle.fixed = (j == 0);
                particleSystem.addParticle(particle);
                if (j > 0)
                {
                    Spring s(index - 1, index, k, (float)sqrt((float)dx * dx + (float)dy * dy));
                    particleSystem.addSpring(s);
                    Spring s2(index - 2, index, k, (float)dx);
                    particleSystem.addSpring(s2);

                }
                ++index;
            }


            // Top particle
            {
                Particle particle(Vector2f(x, y_start + dy), Vector2f(0, 0), Vector2f(0, 0), 1.0);
                particle.fixed = (j == 0);
                particleSystem.addParticle(particle);
                Spring s(index - 1, index, k, (float)dy);
                particleSystem.addSpring(s);
                if (j > 0)
                {
                    Spring s2(index - 2, index, k, (float)dx);
                    particleSystem.addSpring(s2);
                    Spring s3(index - 3, index, k, (float)sqrt((float)dx * dx + (float)dy * dy));
                    particleSystem.addSpring(s3);
                }
                ++index;
            }
        }

    }


    /**
     * TODO Créez votre propre exemple
     */
    static inline void createVotreExemple(ParticleSystem& particleSystem, float k)
    {
        particleSystem.clear();

        // TODO Amusez-vous. Rendu ici, vous le méritez.

    }


}

ParticleSimApplication::ParticleSimApplication() : nanogui::Screen(nanogui::Vector2i(1280, 720), "GTI320 Labo 02 : Physique lineaire", true, false, true, true, false, 4, 1)
, m_particleSystem(), m_stepping(false), m_stiffness(1000.0f), m_maxIter(10), m_solverType(GaussSeidel), m_fpsCounter(0), m_fpsTime(0.0)
{
    initGui();

    createBeam(m_particleSystem, m_stiffness); // le modèle "poutre" est sélectionné à l'initialisation
    m_particleSystem.pack(m_p0, m_v0, m_f0);

    perform_layout();
    reset();
}

void ParticleSimApplication::initGui()
{
    // Initialisation de la fenêtre
    m_window = new nanogui::Window(this, "Particle sim");
    m_window->set_position(nanogui::Vector2i(8, 8));
    m_window->set_layout(new nanogui::GroupLayout());

    // initialisation du canvas où est affiché le système de particules
    m_canvas = new ParticleSimGLCanvas(this);
    m_canvas->set_background_color({ 255, 255, 255, 255 });
    m_canvas->set_size({ 1000, 600 });
    m_canvas->set_draw_border(false);

    // Initialisation de la fenêtre de contrôle
    nanogui::Window* controls = new nanogui::Window(this, "Controls");
    controls->set_position(nanogui::Vector2i(960, 10));
    controls->set_layout(new nanogui::GroupLayout());

    Widget* tools = new Widget(controls);
    tools->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 20));

    // Intervalles des curseur
    const auto stiffnessMinMax = std::make_pair<float, float>(1.0f, sqrt(5000.0f));
    const auto iterMinMax = std::make_pair<float, float>(1.f, 100.f);

    // Affichage du FPS
    m_panelFPS = new Widget(tools);
    m_panelFPS->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 5));
    m_labelFPS = new nanogui::Label(m_panelFPS, "FPS :");
    m_textboxFPS = new nanogui::TextBox(m_panelFPS);
    m_textboxFPS->set_fixed_width(80);
    m_textboxFPS->set_value("0");

    // Affichage du numéro de frame
    m_panelFrames = new Widget(tools);
    m_panelFrames->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 5));
    m_labelFrames = new nanogui::Label(m_panelFrames, "Frame :");
    m_textboxFrames = new nanogui::TextBox(m_panelFrames);
    m_textboxFrames->set_fixed_width(80);
    m_textboxFrames->set_value("0");

    // Boutons pour le choix du solveur
    m_panelSolver = new Widget(tools);
    m_panelSolver->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 5));
    new nanogui::Label(m_panelSolver, "Solver : ");
    nanogui::Button* b = new nanogui::Button(m_panelSolver, "Gauss-Seidel");
    b->set_flags(nanogui::Button::RadioButton);
    b->set_pushed(true);
    b->set_callback([this] { m_solverType = GaussSeidel; });
    b = new nanogui::Button(m_panelSolver, "Gauss-Seidel (coloration)");
    b->set_callback([this] { m_solverType = ColorGaussSeidel; });
    b->set_flags(nanogui::Button::RadioButton);
    b = new nanogui::Button(m_panelSolver, "Cholesky");
    b->set_callback([this] { m_solverType = Cholesky; });
    b->set_flags(nanogui::Button::RadioButton);
    b = new nanogui::Button(m_panelSolver, "None");
    b->set_callback([this] { m_solverType = None; });
    b->set_flags(nanogui::Button::RadioButton);

    // Curseur de rigidité 
    Widget* panelSimControl = new Widget(tools);
    panelSimControl->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 5));
    m_panelStiffness = new nanogui::Widget(panelSimControl);
    m_panelStiffness->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 5));
    m_labelStiffness = new nanogui::Label(m_panelStiffness, "Stiffness : ");
    m_sliderStiffness = new nanogui::Slider(m_panelStiffness);
    m_sliderStiffness->set_range(stiffnessMinMax);
    m_textboxStiffness = new nanogui::TextBox(m_panelStiffness);
    m_sliderStiffness->set_callback([this](float value)
        {
            m_stiffness = value*value;
            onStiffnessSliderChanged();
        });
    m_sliderStiffness->set_value(sqrt(m_stiffness));

    // Curseur du nombre maximum d'itération pour Jacobi et Gauss-Seidel
    Widget* panelMaxIter = new Widget(panelSimControl);
    panelMaxIter->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 5));
    new nanogui::Label(panelMaxIter, "Max iterations : ");
    nanogui::Slider* sliderMaxIter = new nanogui::Slider(panelMaxIter);
    sliderMaxIter->set_range(iterMinMax);
    nanogui::TextBox* textboxMaxIter = new nanogui::TextBox(panelMaxIter);
    textboxMaxIter->set_value(std::to_string(m_maxIter));
    sliderMaxIter->set_value(m_maxIter);
    sliderMaxIter->set_callback([this, textboxMaxIter](float value)
        {
            m_maxIter = (int)value;
            textboxMaxIter->set_value(std::to_string(m_maxIter));
        });

    // Bouton «Simulate»
    nanogui::Button* startStopButton = new nanogui::Button(panelSimControl, "Simulate");
    startStopButton->set_flags(nanogui::Button::ToggleButton);
    startStopButton->set_change_callback([this](bool val)
        {
            m_stepping = val;
            if (val)
            {
                m_prevTime = glfwGetTime();
                draw_all();
            }
        });

    // Bouton «Step»
    nanogui::Button* stepButton = new nanogui::Button(panelSimControl, "Step");
    stepButton->set_callback([this]
        {
            if (!m_stepping) 
            {
                step(deltaT);
                updateFrameCounter();
            }
        });

    // Bouton «Reset»
    nanogui::Button* resetButton = new nanogui::Button(panelSimControl, "Reset");
    resetButton->set_callback([this]
        {
            reset();
        });

    // Boutons pour le choix du modèle
    nanogui::Widget* panelExamples = new nanogui::Widget(tools);
    panelExamples->set_layout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 5));
    new nanogui::Label(panelExamples, "Examples : ");
    nanogui::Button* loadClothButton = new nanogui::Button(panelExamples, "Cloth");
    loadClothButton->set_callback([this]
        {
            createHangingCloth(m_particleSystem, m_stiffness);
            m_particleSystem.pack(m_p0, m_v0, m_f0);
            reset();
        });
    nanogui::Button* loadLargeClothButton = new nanogui::Button(panelExamples, "Large cloth");
    loadLargeClothButton->set_callback([this]
        {
            createLargeHangingCloth(m_particleSystem, m_stiffness);
            m_particleSystem.pack(m_p0, m_v0, m_f0);
            reset();
        });


    nanogui::Button* loadBeamButton = new nanogui::Button(panelExamples, "Beam");
    loadBeamButton->set_callback([this]
        {
            createBeam(m_particleSystem, m_stiffness);
            m_particleSystem.pack(m_p0, m_v0, m_f0);
            reset();
        });

    nanogui::Button* loadRopeButton = new nanogui::Button(panelExamples, "Rope");
    loadRopeButton->set_callback([this]
        {
            createHangingRope(m_particleSystem, m_stiffness);
            m_particleSystem.pack(m_p0, m_v0, m_f0);
            reset();
        });

    nanogui::Button* loadVotreExemple = new nanogui::Button(panelExamples, "Le vôtre");
    loadVotreExemple->set_callback([this]
        {
            createVotreExemple(m_particleSystem, m_stiffness);
            m_particleSystem.pack(m_p0, m_v0, m_f0);
            reset();
        });
}


/**
 * Réaction aux événements déclenchés par le clavier
 */
bool ParticleSimApplication::keyboard_event(int key, int scancode, int action, int modifiers)
{
    if (Screen::keyboard_event(key, scancode, action, modifiers))
        return true;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        set_visible(false);
        return true;
    }
    return false;
}

/**
 * Boucle principale
 *
 * Cette fonction est appelée périodiquement lorsque le programme est actif.
 * C'est ici que tout se passe. Si la simulation est en cours, la fonction
 * `step` est appelée pour faire avancer le système d'un intervalle de temps
 * DELTA_T. Ensuite, l'affichage est mis à jour.
 */
void ParticleSimApplication::draw_contents()
{
    Screen::draw_contents();

    if (m_stepping)
    {
        auto now = glfwGetTime();
        float dt = now - m_prevTime;

        step(deltaT);

        // Update frames per second 
        //
        m_fpsTime += dt;
        ++m_fpsCounter;
        if (m_fpsCounter > 30)
        {
            const float fps = (float)m_fpsCounter / m_fpsTime;
            char buf[64];
            snprintf(buf, sizeof(buf), "%3.1f", fps);
            m_fpsCounter = 0;
            m_fpsTime = 0.0;
            m_textboxFPS->set_value(buf);
        }
        m_prevTime = now;

        updateFrameCounter();
    }

    redraw();
}

/**
 * Appelée lorsque le curseur de rigidité est modifié. La nouvelle rigidité est
 * affectée à tous les ressorts
 */
void ParticleSimApplication::onStiffnessSliderChanged()
{
    // Update all springs with the slider value
    for (Spring& s : getParticleSystem().getSprings())
    {
        s.k = m_stiffness;
    }

    char buf[16];
    snprintf(buf, sizeof(buf), "%4.0f", m_stiffness);
    m_textboxStiffness->set_value(buf);
}

/**
 * Effectue un pas de simulation de taille dt.
 */
void ParticleSimApplication::step(float dt)
{
    // Construction des matrices de masse et de rigidité
    //
    m_particleSystem.buildMassMatrix(m_M);
    m_particleSystem.buildDfDx(m_dfdx);

    // Calcul des forces actuelles sur chacune de sparticules
    //
    m_particleSystem.computeForces();
    m_canvas->applyMouseSpring();

    // Assemblage des vecteurs d'états.
    // 
    m_particleSystem.pack(m_x, m_v, m_f);

    //////////////////////////////////////////////////////////////////////////////////
    // TODO Construire le système d'équation linéaire sous la forme `A*v_plus = b`.
    //      la construction de A et b est donnée dans les diapos du Cours 8.
    //
    //      Note : lors du calcul de b, NE PAS calculer `Mg + Kx` ce
    //      calcul est inutilement coûteux. Pour être plus efficace, on utilise
    //      directement le vecteur d'état m_f.
    //
    //////////////////////////////////////////////////////////////////////////////////
    // Remarque : A et b sont déclarés `const` et ce n'est pas une erreur. C'est
    // pour vous forcer à optimiser votre code.
    //
    // Considérez les exemples suivants :
    // 
    // # Version 1
    // Matrix A;    // constructeur par défaut
    // A = B + C;   // operator+ on construit une matrice et elle est suite copiée avec operator=
    //
    // # Version 2
    // Matrix A = B + C; // la matrice construite dans operator+ est la matrice A.
    //
    // Bilan : Version 1 utilise 2 constructeurs et 1 opérateur de copie
    //         Version 2 utilise un seul constructeur et aucune copie
    //////////////////////////////////////////////////////////////////////////////////
    
    const Matrix<float, Dynamic, Dynamic> A;
    const Vector<float, Dynamic> b;

    // Résolution du système d'équations  `A*v_plus = b`.
    //
    Vector<float, Dynamic> v_plus;
    Vector<float, Dynamic> acc; // vecteur d'accélérations
    switch (m_solverType)
    {
    case GaussSeidel:
        gaussSeidel(A, b, v_plus, m_maxIter);
        break;
    case ColorGaussSeidel:
        gaussSeidelColor(A, b, v_plus, m_graphColor.getPartitions(), m_maxIter);
        break;
    case Cholesky:
        cholesky(A, b, v_plus);
        break;
    default:
    case None:
        // N'utilise pas de solveur, il s'agit de l'implémentation naive de
        // l'intégration d'Euler.
        acc.resize(m_M.rows()); // vecteur d'accélérations
        for (int i = 0; i < m_M.rows(); ++i)
            acc(i) = (1.0 / m_M(i, i)) * m_f(i);
        v_plus = m_v + dt * acc;
        break;
    }

    // TODO 
    //
    // Mise à jour du vecteur d'état de position via l'intégration d'Euler
    // implicite. Les nouvelles position sont calculées à partir des position
    // actuelles m_x et des nouvelles vitesses v_plus. Les nouvelles positions
    // sont stockées directement dans le vecteur m_x.


    // Affecte les valeurs calculées dans le vecteurs d'états aux particules du
    // système
    m_particleSystem.unpack(m_x, v_plus);
}

/**
 * Réinitialisation du système de particules
 */
void ParticleSimApplication::reset()
{
    m_frameCounter = 0;
    updateFrameCounter();
    m_particleSystem.unpack(m_p0, m_v0);
    m_graphColor.color(m_particleSystem);

    onStiffnessSliderChanged();
}

/**
 * Mise à jour du compteur de frames
 */
void ParticleSimApplication::updateFrameCounter()
{
    ++m_frameCounter;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", m_frameCounter);
    m_textboxFrames->set_value(buf);
}

