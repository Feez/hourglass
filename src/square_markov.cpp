/* markov_square.cpp
 *
 * This file is part of EALib.
 *
 * Copyright 2014 David B. Knoester.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <ea/mkv/markov_network_evolution.h>
#include <ea/generational_models/moran_process.h>
#include <ea/fitness_function.h>
#include <ea/cmdline_interface.h>
#include <ea/datafiles/fitness.h>
using namespace ealib;
using namespace mkv;
using namespace std;


/*! Sample fitness function for Markov networks.
 */
struct square_fitness : fitness_function<unary_fitness<double>, constantS, stochasticS> {
    template <typename Individual, typename RNG, typename EA>
    double operator()(Individual& ind, RNG& rng, EA& ea) {
        
        int max_x = 6; // change to config params later...
        int max_y = 6;
        int grid_size = max_x * max_y;
        
        // Must create a WHOLE bunch of markov networks here...
        
        // get the "prototype" phenotype (markov network):
        typename EA::phenotype_type &N = ealib::phenotype(ind, ea);
        
        // and make a few copies:
        vector<typename EA::phenotype_type> as(grid_size, N); // my agents or networks
        
        
        
        
        vector<int> agent_pos (grid_size, -1);
        vector<int> exec_order (grid_size);
        
        for (int i=0; i<grid_size; ++i) {
            exec_order[i] = i;
        }
        
        // get the phenotype (markov network):
        //typename EA::phenotype_type &N = ealib::phenotype(ind, ea);
        
        /* For right now, there isn't a growth process -- just a FULL grid */
        for(int i=0;i<grid_size;i++) {
//            as.push_back(new ealib::phenotype(ind,ea));
            agent_pos[i] = i;
        }
        
        // probably want to reset the RNG for the markov network:
        N.reset(rng.seed());
        
        // now, set the values of the bits in the input vector:
        double f=0.0;
        for(std::size_t i=0; i<128; ++i) {
            // allocate space for the inputs:
            std::vector<int> inputs;//(net.ninput_states(), 0);
            inputs.push_back(rng.bit());
            inputs.push_back(rng.bit());
            
            // update the network n times:
            N.clear();
            N.update(inputs);
            
            if(*N.begin_output() == (inputs[0] ^ inputs[1])) {
                ++f;
            }
        }
        
        // and return some measure of fitness:
        return f;
    }
};

// Evolutionary algorithm definition.
typedef markov_network_evolution
< example_fitness
, recombination::asexual
, generational_models::moran_process< >
> ea_type;

/*! Define the EA's command-line interface.
 */
template <typename EA>
class cli : public cmdline_interface<EA> {
public:
    virtual void gather_options() {
        add_mkv_options(this);
        
        add_option<POPULATION_SIZE>(this);
        add_option<MORAN_REPLACEMENT_RATE_P>(this);
        add_option<RUN_UPDATES>(this);
        add_option<RUN_EPOCHS>(this);
        add_option<RNG_SEED>(this);
        add_option<RECORDING_PERIOD>(this);
    }
    
    
    virtual void gather_tools() {
//        add_tool<analysis::dominant_genetic_graph>(this);
//        add_tool<analysis::dominant_causal_graph>(this);
//        add_tool<analysis::dominant_reduced_graph>(this);
    }
    
    virtual void gather_events(EA& ea) {
        add_event<datafiles::fitness_dat>(ea);
    };
};
LIBEA_CMDLINE_INSTANCE(ea_type, cli);
