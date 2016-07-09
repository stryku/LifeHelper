#include "ProgramFactory.h"
namespace ProgramFactory
{
    ProgramInternals createLocalQt(QWidget *qtViewWidgetParent)
    {
        auto model = new P2Model();
        auto controller = new P2Controller();
        auto inputPropagator =  new P2InputPropagator();
        auto view = new P2QtView(qtViewWidgetParent);

        view->connectWithInput(inputPropagator);
        //inputPropagator->setInputHandler(controller);
        model->registerObserver(controller);
        controller->registerView(view);
        controller->setInputObserver(model);

        auto internals = ProgramInternals(model);


        internals.setController(controller);
        internals.addInput(inputPropagator);
        internals.addView(view);

        return internals;
    }
}
