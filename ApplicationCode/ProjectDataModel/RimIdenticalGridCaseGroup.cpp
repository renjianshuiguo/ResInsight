/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2011-2012 Statoil ASA, Ceetron AS
// 
//  ResInsight is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  ResInsight is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.
// 
//  See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html> 
//  for more details.
//
/////////////////////////////////////////////////////////////////////////////////

#include "RIStdInclude.h"

#include "RimIdenticalGridCaseGroup.h"
#include "RimReservoir.h"
#include "RimReservoirView.h"
#include "RigEclipseCase.h"
#include "RimStatisticalCalculation.h"


CAF_PDM_SOURCE_INIT(RimIdenticalGridCaseGroup, "RimIdenticalGridCaseGroup");

//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
RimIdenticalGridCaseGroup::RimIdenticalGridCaseGroup()
{
    CAF_PDM_InitObject("Identical Grids", "", "", "");

    CAF_PDM_InitFieldNoDefault(&reservoirs, "Reservoirs", "",  "", "", "");
    CAF_PDM_InitFieldNoDefault(&statisticalReservoirs, "StatisticalReservoirs", "",  "", "", "");

    RimStatisticalCalculation* dummyStat = new RimStatisticalCalculation;
    dummyStat->caseName = "Statistics 1";

    statisticalReservoirs.push_back(dummyStat);
}

//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
RimIdenticalGridCaseGroup::~RimIdenticalGridCaseGroup()
{

}

//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void RimIdenticalGridCaseGroup::addCase(RimReservoir* reservoir)
{
    CVF_ASSERT(reservoir);

    if (!reservoir) return;

    RigMainGrid* incomingMainGrid = reservoir->reservoirData()->mainGrid();

    if (m_mainGrid.isNull())
    {
        m_mainGrid = incomingMainGrid;
    }
    else
    {
        if (m_mainGrid.p() != incomingMainGrid)
        {
            CVF_ASSERT(false);
            return;
        }
    }

    reservoirs.push_back(reservoir);
}

//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
RigMainGrid* RimIdenticalGridCaseGroup::mainGrid()
{
    if (m_mainGrid.notNull()) return m_mainGrid.p();

    return NULL;
}

//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
RimStatisticalCalculation* RimIdenticalGridCaseGroup::createAndAppendStatisticalCalculation()
{
    RimStatisticalCalculation* newObject = new RimStatisticalCalculation;

    newObject->caseName = "Statistics 1";

    statisticalReservoirs.push_back(newObject);

    return newObject;
}
