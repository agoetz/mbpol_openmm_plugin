#ifndef OPENMM_AMOEBA_STRETCH_BEND_FORCE_H_
#define OPENMM_AMOEBA_STRETCH_BEND_FORCE_H_

/* -------------------------------------------------------------------------- *
 *                              OpenMMMBPol                                  *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2012 Stanford University and the Authors.      *
 * Authors: Mark Friedrichs, Peter Eastman                                    *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "openmm/Force.h"
#include "internal/windowsExportMBPol.h"
#include <vector>

namespace OpenMM {

/**
 * This class implements the MBPol stretch-bend interaction.
 * 
 * To use it, create a OneBodyForce object then call addOneBody() once for each stretch-bend.  After
 * a stretch-bend has been added, you can modify its force field parameters by calling setOneBodyParameters().
 * This will have no effect on Contexts that already exist unless you call updateParametersInContext().
 */

class OPENMM_EXPORT_MBPOL MBPolOneBodyForce : public Force {

public:

    /**
     * Create an MBPolOneBodyForce.
     */
    MBPolOneBodyForce();

    /**
     * Get the number of stretch-bend terms in the potential function
     */
    int getNumOneBodys() const {
        return stretchBends.size();
    }

    /**
     * Add a stretch-bend term to the force field.
     *
     * @param particle1     the index of the first particle connected by the stretch-bend
     * @param particle2     the index of the second particle connected by the stretch-bend
     * @param particle3     the index of the third particle connected by the stretch-bend
     * @param lengthAB      the equilibrium length of the stretch-bend in bond ab [particle1, particle2], measured in nm
     * @param lengthCB      the equilibrium length of the stretch-bend in bond cb [particle3, particle2], measured in nm
     * @param angle         the equilibrium angle in radians
     * @param k             the force constant for the stretch-bend
     * @return the index of the stretch-bend that was added
     */
    int addOneBody(int particle1, int particle2, int particle3);

    /**
     * Get the force field parameters for a stretch-bend term.
     * 
     * @param index         the index of the stretch-bend for which to get parameters
     * @param particle1     the index of the first particle connected by the stretch-bend
     * @param particle2     the index of the second particle connected by the stretch-bend
     * @param particle3     the index of the third particle connected by the stretch-bend
     * @param lengthAB      the equilibrium length of the stretch-bend in bond ab [particle1, particle2], measured in nm
     * @param lengthCB      the equilibrium length of the stretch-bend in bond cb [particle3, particle2], measured in nm
     * @param angle         the equilibrium angle in radians
     * @param k             the force constant for the stretch-bend
     */
    void getOneBodyParameters(int index, int& particle1, int& particle2, int& particle3 ) const;

    /**
     * Set the force field parameters for a stretch-bend term.
     * 
     * @param index         the index of the stretch-bend for which to set parameters
     * @param particle1     the index of the first particle connected by the stretch-bend
     * @param particle2     the index of the second particle connected by the stretch-bend
     * @param particle3     the index of the third particle connected by the stretch-bend
     * @param lengthAB      the equilibrium length of the stretch-bend in bond ab [particle1, particle2], measured in nm
     * @param lengthCB      the equilibrium length of the stretch-bend in bond cb [particle3, particle2], measured in nm
     * @param angle         the equilibrium angle in radians
     * @param k             the force constant for the stretch-bend
     */
    void setOneBodyParameters(int index, int particle1, int particle2, int particle3 );
    /**
     * Update the per-stretch-bend term parameters in a Context to match those stored in this Force object.  This method provides
     * an efficient method to update certain parameters in an existing Context without needing to reinitialize it.
     * Simply call setOneBodyParameters() to modify this object's parameters, then call updateParametersInState()
     * to copy them over to the Context.
     * 
     * The only information this method updates is the values of per-stretch-bend term parameters.  The set of particles involved
     * in a term cannot be changed, nor can new terms be added.
     */
    void updateParametersInContext(Context& context);

protected:
    ForceImpl* createImpl() const;
private:
    class OneBodyInfo;
    std::vector<OneBodyInfo> stretchBends;
};

class MBPolOneBodyForce::OneBodyInfo {
public:
    int particle1, particle2, particle3;

    OneBodyInfo() {
        particle1 = particle2  = particle3 = -1;

    }
    OneBodyInfo(int particle1, int particle2, int particle3 ) :
                    particle1(particle1), particle2(particle2), particle3(particle3) {
     
    }
};

} // namespace OpenMM

#endif /*OPENMM_AMOEBA_STRETCH_BEND_FORCE_H_*/
