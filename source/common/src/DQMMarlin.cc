  /// \file DQMMarlin.cc
/*
 *
 * DQMMarlin.cc source template automatically generated by a class generator
 * Creation date : lun. mars 7 2016
 *
 * This file is part of DQM4ILC libraries.
 *
 * DQM4ILC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4ILC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4ILC.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#include "dqm4ilc/DQMMarlin.h"

// -- lcio headers
#include "EVENT/LCIO.h"

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"
#include "dqm4hep/DQMModuleApi.h"
#include "dqm4hep/DQMLogging.h"
#include "dqm4hep/DQMEvent.h"
#include "dqm4hep/DQMPluginManager.h"

// -- marlin headers
#include "marlin/tinyxml.h"
#include "marlin/IParser.h"
#include "marlin/Parser.h"
#include "marlin/XMLParser.h"
#include "marlin/Global.h"
#include "marlin/ProcessorMgr.h"

// -- gear headers
#include "gearimpl/Util.h"
#include "gearxml/GearXML.h"
#include "gearxml/MergeXML.h"
#include "gearimpl/GearMgrImpl.h"

// -- streamlog headers
#include "streamlog/streamlog.h"

namespace dqm4ilc
{

DQMMarlin::DQMMarlin()
{
	/* nop */
}

//-------------------------------------------------------------------------------------------------

DQMMarlin::~DQMMarlin()
{
	/* nop */
}

//-------------------------------------------------------------------------------------------------

void DQMMarlin::init(const std::string &steeringFileName)
{
	std::string marlinDlls;

	char *pMarlinDlls = getenv("MARLIN_DLL");

	if( ! pMarlinDlls )
	{
		std::stringstream ss;
		ss << "MarlinModule : MARLIN_DLL env var not set !";
		std::cout << ss.str() << std::endl;

		throw EVENT::Exception(ss.str());
	}

	marlinDlls = pMarlinDlls;
	dqm4hep::StringVector libraryList;
	dqm4hep::DQM4HEP::tokenize(marlinDlls, libraryList, ":");

	if(dqm4hep::STATUS_CODE_SUCCESS != dqm4hep::DQMPluginManager::instance()->loadLibraries(libraryList))
	{
		std::stringstream ss;
		ss << "Failed to load Marlin processors !";
		std::cout << ss.str() << std::endl;

		throw EVENT::Exception(ss.str());
	}

	marlin::IParser *pParser = 0;

    // for now allow xml and old steering
    std::string filen(  steeringFileName ) ;

    if( filen.rfind(".xml") == std::string::npos  // .xml not found at all
    		|| !( filen.rfind(".xml") + strlen(".xml") == filen.length() ) )
    {
        pParser = new marlin::Parser( steeringFileName );
    }
    else
    {
        pParser = new marlin::XMLParser( steeringFileName );
    }

    pParser->parse();

    marlin::Global::parameters = pParser->getParameters("Global").get()  ;

    if( 0 == marlin::Global::parameters )
    {
		std::stringstream ss;
		ss << "Could not get global parameters from steering file !";
		std::cout << ss.str() << std::endl;

		throw EVENT::Exception(ss.str());
    }

    // initialize streamlog
    streamlog::out.init( std::cout, "DQMMarlinModule" ) ;

    streamlog::out.addLevelName<streamlog::DEBUG>() ;
    streamlog::out.addLevelName<streamlog::DEBUG0>() ;
    streamlog::out.addLevelName<streamlog::DEBUG1>() ;
    streamlog::out.addLevelName<streamlog::DEBUG2>() ;
    streamlog::out.addLevelName<streamlog::DEBUG3>() ;
    streamlog::out.addLevelName<streamlog::DEBUG4>() ;
    streamlog::out.addLevelName<streamlog::DEBUG5>() ;
    streamlog::out.addLevelName<streamlog::DEBUG6>() ;
    streamlog::out.addLevelName<streamlog::DEBUG7>() ;
    streamlog::out.addLevelName<streamlog::DEBUG8>() ;
    streamlog::out.addLevelName<streamlog::DEBUG9>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE0>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE1>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE2>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE3>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE4>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE5>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE6>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE7>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE8>() ;
    streamlog::out.addLevelName<streamlog::MESSAGE9>() ;
    streamlog::out.addLevelName<streamlog::WARNING>() ;
    streamlog::out.addLevelName<streamlog::WARNING0>() ;
    streamlog::out.addLevelName<streamlog::WARNING1>() ;
    streamlog::out.addLevelName<streamlog::WARNING2>() ;
    streamlog::out.addLevelName<streamlog::WARNING3>() ;
    streamlog::out.addLevelName<streamlog::WARNING4>() ;
    streamlog::out.addLevelName<streamlog::WARNING5>() ;
    streamlog::out.addLevelName<streamlog::WARNING6>() ;
    streamlog::out.addLevelName<streamlog::WARNING7>() ;
    streamlog::out.addLevelName<streamlog::WARNING8>() ;
    streamlog::out.addLevelName<streamlog::WARNING9>() ;
    streamlog::out.addLevelName<streamlog::ERROR>() ;
    streamlog::out.addLevelName<streamlog::ERROR0>() ;
    streamlog::out.addLevelName<streamlog::ERROR1>() ;
    streamlog::out.addLevelName<streamlog::ERROR2>() ;
    streamlog::out.addLevelName<streamlog::ERROR3>() ;
    streamlog::out.addLevelName<streamlog::ERROR4>() ;
    streamlog::out.addLevelName<streamlog::ERROR5>() ;
    streamlog::out.addLevelName<streamlog::ERROR6>() ;
    streamlog::out.addLevelName<streamlog::ERROR7>() ;
    streamlog::out.addLevelName<streamlog::ERROR8>() ;
    streamlog::out.addLevelName<streamlog::ERROR9>() ;
    streamlog::out.addLevelName<streamlog::SILENT>() ;

    std::string verbosity = marlin::Global::parameters->getStringVal("Verbosity");
    streamlog::logscope scope( streamlog::out ) ;

    scope.setLevel( verbosity ) ;

    // create processors
    this->createProcessors(pParser);

    // handle gear file
    std::string gearFile = marlin::Global::parameters->getStringVal("GearXMLFile");

    if( gearFile.size() > 0 )
    {
        gear::GearXML gearXML( gearFile );
        marlin::Global::GEAR = gearXML.createGearMgr();

        streamlog_out(MESSAGE) << "---- Gear file : " << gearFile << std::endl;
    }
    else
    {
		streamlog_out(WARNING) << "---- no GEAR XML file given  ---------" << std::endl;
    	marlin::Global::GEAR = new gear::GearMgrImpl();
    }

    // initialize marlin
    try
    {
    	marlin::ProcessorMgr::instance()->init();
    }
    catch(EVENT::Exception &exception)
    {
		std::stringstream ss;
		ss << "Couldn't initialize marlin application : " << exception.what();
		streamlog_out(ERROR) << ss.str() << std::endl;

		throw EVENT::Exception(ss.str());
    }
    catch(...)
    {
		std::stringstream ss;
		ss << "Couldn't initialize marlin application ! Unknown exception !";
		streamlog_out(ERROR) << ss.str() << std::endl;

		throw EVENT::Exception(ss.str());
    }
}

//-------------------------------------------------------------------------------------------------

void DQMMarlin::processEvent(EVENT::LCEvent *pLCEvent)
{
	marlin::ProcessorMgr::instance()->processEvent(pLCEvent);
}

//-------------------------------------------------------------------------------------------------

void DQMMarlin::end()
{
	// end module in marlin framework
	marlin::ProcessorMgr::instance()->end();

	if( marlin::Global::GEAR != 0 )
		delete marlin::Global::GEAR;
}

//-------------------------------------------------------------------------------------------------

void DQMMarlin::createProcessors(marlin::IParser *pParser)
{
    dqm4hep::StringVector activeProcessors;
    marlin::Global::parameters->getStringVals("ActiveProcessors", activeProcessors);

    dqm4hep::StringVector procConds;
    marlin::Global::parameters->getStringVals("ProcessorConditions", procConds);

    bool useConditions = ( activeProcessors.size() == procConds.size() ) ;

    for(unsigned int i=0 ; i<  activeProcessors.size() ; i++ )
    {
				std::shared_ptr<marlin::StringParameters> pParameters = pParser->getParameters( activeProcessors[i] )  ;

        if( pParameters != 0 )
        {
            std::string type = pParameters->getStringVal("ProcessorType") ;

            if( useConditions )
                marlin::ProcessorMgr::instance()->addActiveProcessor( type , activeProcessors[i] , pParameters , procConds[i] )  ;
            else
            	marlin::ProcessorMgr::instance()->addActiveProcessor( type , activeProcessors[i] , pParameters )  ;
        }
        else
        {
        	std::stringstream ss;
        	ss <<  "Undefined processor : " << activeProcessors[i];
            streamlog_out(ERROR) << ss.str() << std::endl;

            throw EVENT::Exception(ss.str());
        }
    }
}

}

