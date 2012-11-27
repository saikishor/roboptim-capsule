// Copyright (C) 2012 by Antonio El Khoury.
//
// This file is part of the roboptim-capsule.
//
// roboptim-capsule is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim-capsule is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim-capsule.  If not, see <http://www.gnu.org/licenses/>.

#define BOOST_TEST_MODULE fitter

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <roboptim/capsule/util.hh>
#include <roboptim/capsule/fitter.hh>

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (fitter)
{
  using namespace roboptim::capsule;

  // Build a cubic polyhedron.
  polyhedron_t polyhedron;
  value_type halfLength = 0.5;

  polyhedron.push_back (point_t (-halfLength, -halfLength, -halfLength));
  polyhedron.push_back (point_t (-halfLength, -halfLength, halfLength));
  polyhedron.push_back (point_t (-halfLength, halfLength, -halfLength));
  polyhedron.push_back (point_t (-halfLength, halfLength, halfLength));
  polyhedron.push_back (point_t (halfLength, -halfLength, -halfLength));
  polyhedron.push_back (point_t (halfLength, -halfLength, halfLength));
  polyhedron.push_back (point_t (halfLength, halfLength, -halfLength));
  polyhedron.push_back (point_t (halfLength, halfLength, halfLength));

  polyhedrons_t polyhedrons;
  polyhedrons.push_back (polyhedron);

  // Create fitter. It is used to find the best fitting capsule on the
  // polyhedron.
  Fitter fitter (polyhedrons);

  // Define initial capsule parameters. The segment must be inside the
  // polyhedron, and the capsule must contain the polyhedron.
  argument_t initParam (7);

  // First end point.
  initParam[0] = 0.;
  initParam[1] = 0.;
  initParam[2] = - halfLength / 4;
  // Second end point.
  initParam[3] = 0.;
  initParam[4] = 0.;
  initParam[5] = halfLength / 4;
  // Radius.
  initParam[6] = 100 * halfLength;
  
  // Compute best fitting capsule.
  fitter.computeBestFitCapsule (initParam);
  std::cout << fitter << std::endl;
}
