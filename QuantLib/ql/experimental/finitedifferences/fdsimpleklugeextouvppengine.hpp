/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2011 Klaus Spanderen

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file fdsimpleextoujumpswingengine.hpp
    \brief Finite Differences engine for simple swing options
*/

#ifndef quantlib_fd_simple_kluge_ou_vpp_engine_hpp
#define quantlib_fd_simple_kluge_ou_vpp_engine_hpp

#include <ql/pricingengine.hpp>
#include <ql/experimental/finitedifferences/vanillavppoption.hpp>
#include <ql/experimental/finitedifferences/fdmbackwardsolver.hpp>
#include <ql/experimental/finitedifferences/fdmextoujumpmodelinnervalue.hpp>

namespace QuantLib {

    //! Finite-Differences engine for simple vpp options

    class YieldTermStructure;
    class KlugeExtOUProcess;

    class FdSimpleKlugeExtOUVPPEngine
        : public GenericEngine<VanillaVPPOption::arguments,
                               VanillaVPPOption::results> {
      public:
        typedef FdmExtOUJumpModelInnerValue::Shape Shape;

        FdSimpleKlugeExtOUVPPEngine(
            const boost::shared_ptr<KlugeExtOUProcess>& process,
            const boost::shared_ptr<YieldTermStructure>& rTS,
            Real carbonPrice,
            Size tGrid = 1 , Size xGrid = 50,
            Size yGrid = 10, Size gGrid = 20,
            const boost::shared_ptr<Shape>& gasShape
                                                = boost::shared_ptr<Shape>(),
            const boost::shared_ptr<Shape>& powerShape
                                                = boost::shared_ptr<Shape>(),
            const FdmSchemeDesc& schemeDesc = FdmSchemeDesc::Hundsdorfer());

        void calculate() const;

      private:
        const boost::shared_ptr<KlugeExtOUProcess> process_;
        const boost::shared_ptr<YieldTermStructure> rTS_;
        const Real carbonPrice_;
        const boost::shared_ptr<Shape> gasShape_;
        const boost::shared_ptr<Shape> powerShape_;
        const Size tGrid_, xGrid_, yGrid_, gGrid_;
        const FdmSchemeDesc schemeDesc_;
    };
}

#endif

