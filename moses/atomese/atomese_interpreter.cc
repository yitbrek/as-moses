/** atomese_interpreter.cc ---
*
* Copyright (C) 2018 OpenCog Foundation
*
* Author: Yidnekachew Wondimu,Bitseat Tadesse and Yenatfanta Shifferaw
*
*/
#include <opencog/atoms/base/Link.h>
#include <opencog/atoms/base/Node.h>
#include <opencog/atomspace/AtomSpace.h>

#include "/home/bitseat/Desktop/as-moses/moses/comboreduct/atomese_representation/atomese_representation.h"
#include <opencog/guile/SchemeEval.h>
#include <opencog/atoms/execution/Instantiator.h>


using namespace opencog;
using namespace std;

AtomSpace *as;
SchemeEval *eval;


Handle interpreter(const Handle &repr){

    Handle check = repr->getOutgoingSet()[1];
    HandleSeq result = check->getOutgoingSet();
    HandleSeq rowseq;

    //store the rows
    for(const Handle &h : result){
        Handle nextresult = h->getOutgoingSet()[0];
        rowseq.push_back(nextresult);
    }

    Handle inner_set_link = repr->getOutgoingSet()[1];

    HandleSeq inner_list_link;
    HandleSeq outputs;
    HandleSeq setoutputs;
    //get the inner list link
    for (const Handle &h : inner_set_link->getOutgoingSet()){
        inner_list_link.push_back(h->getOutgoingSet()[1]);
    }

    unsigned long j=0;
    //execute the PlusLink and return the result
    for(const Handle &handle : inner_list_link){

        unsigned long i = handle->getOutgoingSet().size();
        HandleSeq inputs;
        //assuming the last item is the output, get all the input features before it.
        for(Handle h : handle->getOutgoingSet()){
            if(i!=1){
                inputs.push_back(h);
            }

            i--;
        }
        as = new AtomSpace();
        eval = new SchemeEval(as);
        eval->eval("(use-modules (opencog exec))");

        Handle plus_linked = createLink(inputs, PLUS_LINK);
        Handle list_linked = createLink(inputs, LIST_LINK);
        setoutputs.push_back(list_linked);

        Handle plus_linked_atom = as->add_atom(plus_linked);
        Instantiator inst(as);
        Handle answer = inst.execute(plus_linked_atom);
        Handle ss = createLink(LIST_LINK,
                               rowseq[j++],
                               answer);
        outputs.push_back(ss);


    }

    Handle final_output = createLink(outputs, SET_LINK);
    Handle domain = createLink(setoutputs, SET_LINK);

    cout << final_output->to_short_string();
    cout << domain->to_short_string();
}

int main() {
    //get the atomese representation of csv file
    Handle repr = atomese::load_atomese("/home/bitseat/bitcog/as-moses/moses/atomese/test1.csv");

    Handle h = interpreter(repr);

    return 0;

}