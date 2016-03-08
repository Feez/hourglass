//
//  body_plans.h
//  hourglass
//
//  Created by Heather Goldsby on 3/7/16.
//  Copyright © 2016 Michigan State University. All rights reserved.
//

#ifndef body_plans_h
#define body_plans_h


LIBEA_MD_DECL(BODYPLAN, "ea.hourglass.body_plans.body_plan", double); //


/* Note: These fitness functions assume a 6x6 grid. */


/* All 00 */
template <typename EA>
double body_plan0 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;

    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            continue;
        }
        
        if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
            ++f_00;
        }
    }
    
    double e = f_00;
    double f = pow(1.5, e);
        
    return f;
}


/* Half 00, half 01 */
template <typename EA>
double body_plan1 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            continue;
        }
        
        if (agent_y < 3) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        } else {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
    }
    
    double e = f_00 + f_01;
    double f = pow(1.5, e);
    
    return f;
}

/* Three stripes - 00, 11, 01 */
template <typename EA>
double body_plan2 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            continue;
        }
        
        if (agent_y < 2) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        } else if (agent_y < 4){
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        } else {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
    }
    
    double e = f_00 + f_01 + f_11;
    double f = pow(1.5, e);
    
    return f;
}

/* Gastrulation */
template <typename EA>
double body_plan3 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            continue;
        }
        
        if ((agent_y == 0) || (agent_x ==0) || (agent_x==5) || ((agent_x == 1) && (agent_y == 5)) || ((agent_x == 4) && (agent_y == 5))) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 1)) || ((agent_x == 2) && (agent_y == 1)) || ((agent_x == 3) && (agent_y == 1)) ||
            ((agent_x == 4) && (agent_y == 1)) || ((agent_x == 1) && (agent_y == 2)) || ((agent_x == 1) && (agent_y == 3)) ||
            ((agent_x == 1) && (agent_y == 4)) || ((agent_x == 4) && (agent_y == 2)) || ((agent_x == 4) && (agent_y == 3)) ||
            ((agent_x == 4) && (agent_y == 4))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        }
        
        if (((agent_x == 2) && (agent_y == 2)) || ((agent_x == 3) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 3)) ||
            ((agent_x == 3) && (agent_y == 3)) || ((agent_x == 2) && (agent_y == 4)) || ((agent_x == 3) && (agent_y == 4)) ||
            ((agent_x == 2) && (agent_y == 5)) || ((agent_x == 3) && (agent_y == 5))) {
            
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
            
            
        
        
    }
    
    double e = f_00 + f_01 + f_11;
    double f = pow(1.5, e);
    
    return f;
}
    

/* First body cavity */
template <typename EA>
double body_plan4 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    double f_na = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            if (((agent_x == 2) && (agent_y == 2)) || ((agent_x == 3) && (agent_y == 2)) ) {
                f_na++;
            }
            continue;
        }
        
        
        if ((agent_y == 0) || (agent_x ==0) || (agent_x==5) || ((agent_x == 1) && (agent_y == 5)) || ((agent_x == 4) && (agent_y == 5))) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 1)) || ((agent_x == 2) && (agent_y == 1)) || ((agent_x == 3) && (agent_y == 1)) ||
            ((agent_x == 4) && (agent_y == 1)) || ((agent_x == 1) && (agent_y == 2)) || ((agent_x == 1) && (agent_y == 3)) ||
            ((agent_x == 1) && (agent_y == 4)) || ((agent_x == 4) && (agent_y == 2)) || ((agent_x == 4) && (agent_y == 3)) ||
            ((agent_x == 4) && (agent_y == 4)) || ((agent_x == 2) && (agent_y == 3)) || ((agent_x == 3) && (agent_y == 3)) ) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        }
        
        if (((agent_x == 2) && (agent_y == 4)) || ((agent_x == 3) && (agent_y == 4)) ||
            ((agent_x == 2) && (agent_y == 5)) || ((agent_x == 3) && (agent_y == 5))) {
            
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
        
        
        
        
        
    }
    
    double e = f_00 + f_01 + f_11 + f_na;
    double f = pow(1.5, e);
    
    return f;
}





/* neural tissue arrives */
template <typename EA>
double body_plan5 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    double f_10 = 0.0;
    double f_na = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            if (((agent_x == 1) && (agent_y == 3)) || ((agent_x == 4) && (agent_y == 3)) ) {
                f_na++;
            }
            continue;
        }
        
        
        
        if ((agent_y == 0) || (agent_x ==0) || (agent_x==5) || ((agent_x == 1) && (agent_y == 5)) || ((agent_x == 4) && (agent_y == 5))) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 1)) || ((agent_x == 2) && (agent_y == 1)) || ((agent_x == 3) && (agent_y == 1)) ||
            ((agent_x == 4) && (agent_y == 1))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 0)){
                ++f_10;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 2)) || ((agent_x == 3) && (agent_y == 2)) ||
            ((agent_x == 4) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 3)) || ((agent_x == 3) && (agent_y == 3))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 4)) || ((agent_x == 2) && (agent_y == 4)) || ((agent_x == 3) && (agent_y == 4)) ||
            (((agent_x == 4) && (agent_y == 4)) || (agent_x == 2) && (agent_y == 5)) || ((agent_x == 3) && (agent_y == 5))) {
            
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
        
    }
    
    double e = f_00 + f_01 + f_11 + f_10 + f_na;
    double f = pow(1.5, e);
    
    return f;
}




/* mammal 1  */
template <typename EA>
double body_plan6 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    double f_10 = 0.0;
    double f_na = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            if (((agent_x == 0) && (agent_y == 3)) || ((agent_x == 5) && (agent_y == 3)) ) {
                f_na++;
            }
            continue;
        }
        
        
        
        if ((agent_y == 0) || (agent_x ==0) || (agent_x==5) || ((agent_x == 1) && (agent_y == 5)) || ((agent_x == 4) && (agent_y == 5))
            || ((agent_x == 1) && (agent_y == 3)) || ((agent_x == 4) && (agent_y == 3))) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 1)) || ((agent_x == 2) && (agent_y == 1)) || ((agent_x == 3) && (agent_y == 1)) ||
            ((agent_x == 4) && (agent_y == 1))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 0)){
                ++f_10;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 2)) || ((agent_x == 3) && (agent_y == 2)) ||
            ((agent_x == 4) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 3)) || ((agent_x == 3) && (agent_y == 3))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 4)) || ((agent_x == 2) && (agent_y == 4)) || ((agent_x == 3) && (agent_y == 4)) ||
            (((agent_x == 4) && (agent_y == 4)) || (agent_x == 2) && (agent_y == 5)) || ((agent_x == 3) && (agent_y == 5))) {
            
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
    }
    
    double e = f_00 + f_01 + f_11 + f_10 + f_na;
    double f = pow(1.5, e);
    
    return f;
}

/* mammal 2 */
template <typename EA>
double body_plan7 (int grid_size, int max_x, int max_y, std::vector<int>& agent_pos, std::vector<typename EA::phenotype_type>& as, EA& ea) {
    assert(max_x == 6);
    assert(max_y == 6);
    
    double f_00 = 0.0;
    double f_01 = 0.0;
    double f_11 = 0.0;
    double f_10 = 0.0;
    double f_na = 0.0;
    
    // Compute fitness. All 00
    for (int xy = 0; xy<grid_size; xy++) {
        
        // set the input states...
        int agent_x = floor(xy / max_x);
        int agent_y = xy % max_x;
        
        int p = agent_pos[xy];
        
        // no agent
        if (p == -1) {
            if (((agent_x == 1) && (agent_y == 3)) || ((agent_x == 4) && (agent_y == 3)) || ((agent_x == 0) && (agent_y == 5)) ||
                ((agent_x == 5) && (agent_y == 5)) ) {
                f_na++;
            }
            continue;
        }
        
        
        
        if ((agent_y == 0) || (agent_x ==0) || (agent_x==5) || ((agent_x == 1) && (agent_y == 5)) || ((agent_x == 4) && (agent_y == 5))) {
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 0)){
                ++f_00;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 1)) || ((agent_x == 2) && (agent_y == 1)) || ((agent_x == 3) && (agent_y == 1)) ||
            ((agent_x == 4) && (agent_y == 1))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 0)){
                ++f_10;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 2)) || ((agent_x == 2) && (agent_y == 2)) || ((agent_x == 3) && (agent_y == 2)) ||
            ((agent_x == 4) && (agent_y == 2))) {
            if (((as[p]).output(0) == 1) &&  ((as[p]).output(1) == 1)){
                ++f_11;
            }
        }
        
        if (((agent_x == 1) && (agent_y == 4)) || ((agent_x == 2) && (agent_y == 4)) || ((agent_x == 3) && (agent_y == 4)) ||
            (((agent_x == 4) && (agent_y == 4)) || (agent_x == 2) && (agent_y == 5)) || ((agent_x == 3) && (agent_y == 5)) ||
            ((agent_x == 2) && (agent_y == 3)) || ((agent_x == 3) && (agent_y == 3))) {
            
            if (((as[p]).output(0) == 0) &&  ((as[p]).output(1) == 1)){
                ++f_01;
            }
        }
        
        
    }
    
    double e = f_00 + f_01 + f_11 + f_10 + f_na;
    double f = pow(1.5, e);
    
    return f;
}




#endif /* body_plans_h */
