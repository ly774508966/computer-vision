#ifndef TARGET_ANALYZER_H_INCLUDED
#define TARGET_ANALYZER_H_INCLUDED

/**
    @file target_analyzer.h
  
    @brief Module for geolocating targets using their pixel locations
           and photo metadata, determine target type and calculate 
           possible error
  
**/

#include "frame.h"

class TargetAnalyzer{
    public:
        TargetAnalyzer();
        
        ~TargetAnalyzer();

        /**
         * @brief Puts the given frame into the analysis queue
         * Frame will be freed after analysis
         *
         * @param f Frame containing the targets to analyze
         */
        void analyze_targets_in_frame(Frame * f);

        /**
         * @brief retrieves a vector containing all of the unique Targets that 
         *        have been indentified. 
         *        The caller of the function should not delete the Targets as they
         *        will be deleted by the TargetAnalyzer destructor
         *        
         * @return vector containing the unique Targets which have been analyzed
         */
        vector<Target *> get_processed();
};

#endif // TARGET_ANALYZER_H_INCLUDED
