#include <ProgramInternalsCreators.h>

#include <internals/view/QtView.h>

namespace ProgramInternalsCreators
{
    ProgramInternals createLocalQt( QWidget *qtViewWidgetParent )
    {
        auto model = new P2::Model::Model();
        auto controller = new P2::Controller::Controller();
        auto inputPropagator = new P2::Input::InputPropagator();
        auto view = new P2::View::QtView( qtViewWidgetParent );

        view->connectWithInput( inputPropagator );
        model->registerObserver( controller );
        controller->registerView( view );
        controller->setInputObserver( model );

        auto internals = ProgramInternals( model );


        internals.setController( controller );
        internals.addInput( inputPropagator );
        internals.addView( view );

        return internals;
    }
}
