#ifndef __AI_H__
#define __AI_H__
/**
 * ai.h
 * Defines an interface for the AI object
 * 
 * Author: Chun Li and Weichen Zhou
 * Created: Nov. 20, 2013.
 */

class AI {
        AIImpl *a;
        getAIImpl(int level);
    public:
        AI(int level = 1);
};

#endif /* ai.h */
