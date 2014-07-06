/* -------------------------------------------------------------------------- *
 *                                OpenMMMBPol                                *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2008-2009 Stanford University and the Authors.      *
 * Authors:                                                                   *
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
#include "openmm/OpenMMException.h"
#include "openmm/MBPolDispersionForce.h"
#include "openmm/internal/MBPolDispersionForceImpl.h"

using namespace  OpenMM;
using namespace MBPolPlugin;
using std::string;
using std::vector;

MBPolDispersionForce::MBPolDispersionForce() : nonbondedMethod(CutoffNonPeriodic), cutoff(1.0e+10) {
}

int MBPolDispersionForce::addParticle(const std::vector<int> & particleIndices ) {
    parameters.push_back(DispersionInfo(particleIndices));
    return parameters.size()-1;
}

int MBPolDispersionForce::getNumMolecules() const {
    return parameters.size();
}

void MBPolDispersionForce::getParticleParameters(int particleIndex, std::vector<int>& particleIndices ) const {
    particleIndices     = parameters[particleIndex].particleIndices;
}

void MBPolDispersionForce::setParticleParameters(int particleIndex, std::vector<int>& particleIndices  ) {
      parameters[particleIndex].particleIndices =particleIndices;
}

void MBPolDispersionForce::setCutoff( double inputCutoff ){
    cutoff = inputCutoff;
}

double MBPolDispersionForce::getCutoff( void ) const {
    return cutoff;
}

MBPolDispersionForce::NonbondedMethod MBPolDispersionForce::getNonbondedMethod() const {
    return nonbondedMethod;
}

void MBPolDispersionForce::setNonbondedMethod(NonbondedMethod method) {
    nonbondedMethod = method;
}

ForceImpl* MBPolDispersionForce::createImpl() const {
    return new MBPolDispersionForceImpl(*this);
}

void MBPolDispersionForce::updateParametersInContext(Context& context) {
    dynamic_cast<MBPolDispersionForceImpl&>(getImplInContext(context)).updateParametersInContext(getContextImpl(context));
}
