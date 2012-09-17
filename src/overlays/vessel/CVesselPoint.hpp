// INDENTING (emacs/vi): -*- mode:c++; tab-width:2; c-basic-offset:2; intent-tabs-mode:nil; -*- ex: set tabstop=2 expandtab:

/*
 * Qt Virtual Chart Table (QVCT)
 * Copyright (C) 2012 Cedric Dufour <http://cedric.dufour.name>
 * Author: Cedric Dufour <http://cedric.dufour.name>
 *
 * The Qt Virtual Chart Table (QVCT) is free software:
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, Version 3.
 *
 * The Qt Virtual Chart Table (QVCT) is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 */

#ifndef QVCT_CVESSELPOINT_HPP
#define QVCT_CVESSELPOINT_HPP

// QT
#include <QDataStream>
#include <QDomElement> // QtXml module
#include <QPainter>
#include <QPointF>
#include <QTreeWidgetItem>
#include <QXmlStreamWriter>

// QVCT
#include "data/CDataCourseValidity.hpp"
#include "data/CDataPositionValidity.hpp"
#include "data/CDataTimeValidity.hpp"
#include "overlays/COverlayCourse.hpp"


/// [UI] Vessel overlay point (item) / vessel
/**
 *  This class implements the overlay point (item) for the vessel overlay.
 *  @author Cedric Dufour <http://cedric.dufour.name>
 */
class CVesselPoint: public COverlayCourse, public CDataTimeValidity, public CDataPositionValidity, public CDataCourseValidityGA
{

  //------------------------------------------------------------------------------
  // FIELDS
  //------------------------------------------------------------------------------

private:
  /// Dynamic flag (vessel automatically generated by a dynamic flotilla)
  bool bDynamic;

  /// Vessel's type
  QString qsType;
  /// Vessel's description
  QString qsDescription;
  /// Vessel's comment
  QString qsComment;
  /// Vessel's symbol
  /** @see CMainWindow::symbolExists(), CMainWindow::symbolPixmap() */
  QString qsSymbol;
  /// Vessel's URL
  QString qsUrl;

  /// Vessel point's fix type
  int eFixType;
  /// Vessel point's satellites count
  int iSatelliteCount;
  /// Vessel point's horizontal Dilution-of-Precision (HDOP)
  double fdDopHorizontal;
  /// Vessel point's vertical Dilution-of-Precision (VDOP)
  double fdDopVertical;

  /// Vessel's track recording rate, in seconds
  int iTrackRecordRate;
  /// Vessel's track recording status
  bool bTrackRecord;
  /// Vessel's track last recording time
  double fdTrackRecordTimeLast;
  /// Vessel's track last recorded bearing
  double fdTrackRecordBearingLast;


  //------------------------------------------------------------------------------
  // CONSTRUCTORS / DESTRUCTOR
  //------------------------------------------------------------------------------

public:
  CVesselPoint( const QString& _rqsName, bool _bDynamic = false );
  CVesselPoint( const QString& _rqsName, const CDataPosition& _roDataPosition );
  virtual ~CVesselPoint();


  //------------------------------------------------------------------------------
  // METHODS: COverlayObject (implement/override)
  //------------------------------------------------------------------------------

public:
  virtual void serialize( QDataStream& _rqDataStream ) const;
  virtual void unserialize( QDataStream& _rqDataStream );

public:
  virtual COverlay* useOverlay() { return (COverlay*)QTreeWidgetItem::parent()->parent(); };

public:
  virtual void draw( const CChart* _poChart, QPainter* _pqPainter );
  virtual void showDetail();
  virtual void showEdit();


  //------------------------------------------------------------------------------
  // METHODS: COverlayPoint (implement/override)
  //------------------------------------------------------------------------------

public:
  virtual bool matchScrPosition( const CChart* _poChart, const QPointF& _rqPointFScrPosition ) const;


  //------------------------------------------------------------------------------
  // METHODS: COverlayVisibility (override)
  //------------------------------------------------------------------------------

public:
  virtual void toggleVisible();


  //------------------------------------------------------------------------------
  // METHODS
  //------------------------------------------------------------------------------

  // SETTERS
public:
  /// Toggles this vessel's selection status
  void toggleMultiSelected();
  /// Sets this vessel's type
  void setType( const QString& _rqsType ) { qsType = _rqsType; };
  /// Sets this vessel's description
  void setDescription( const QString& _rqsDescription ) { qsDescription = _rqsDescription; };
  /// Sets this vessel's comment
  void setComment( const QString& _rqsComment ) { qsComment = _rqsComment; };
  /// Sets this vessel's symbol
  void setSymbol( const QString& _rqsSymbol ) { qsSymbol = _rqsSymbol; };
  /// Sets this vessel's URL
  void setUrl( const QString& _rqsUrl ) { qsUrl = _rqsUrl; };

public:
  /// Sets this vessel point's fix type
  void setFixType( int _eFixType ) { eFixType = _eFixType; };
  /// Sets this vessel point's satellite count
  void setSatelliteCount( int _iSatelliteCount ) { iSatelliteCount = _iSatelliteCount; };
  /// Sets this vessel point's horizontal Dilution-of-Precision (HDOP)
  void setDopHorizontal( double _fdDopHorizontal ) { fdDopHorizontal = _fdDopHorizontal; };
  /// Sets this vessel point's vertical Dilution-of-Precision (VDOP)
  void setDopVertical( double _fdDopVertical ) { fdDopVertical = _fdDopVertical; };

public:
  /// Sets this vessel's track recording rate, in seconds
  void setTrackRecordRate( int _iTrackRecordRate ) { iTrackRecordRate = _iTrackRecordRate; };
  /// Sets this vessel's track recording status
  bool setTrackRecord( bool _bTrackRecord );

  // GETTERS
public:
  /// Returns whether the vessel is dynamically generated
  bool isDynamic() { return bDynamic; }
  /// Returns whether this vessel's devices are all connected
  bool isDeviceConnected() const;

  /// Returns this vessel's type
  QString getType() const { return qsType; };
  /// Returns this vessel's description
  QString getDescription() const { return qsDescription; };
  /// Returns this vessel's comment
  QString getComment() const { return qsComment; };
  /// Returns this vessel's symbol
  QString getSymbol() const { return qsSymbol; };
  /// Returns this vessel's URL
  QString getUrl() const { return qsUrl; };

public:
  /// Sets this vessel point's fix type
  int getFixType() { return eFixType; };
  /// Sets this vessel point's satellite count
  int getSatelliteCount() { return iSatelliteCount; };
  /// Sets this vessel point's horizontal Dilution-of-Precision (HDOP)
  double getDopHorizontal() { return fdDopHorizontal; };
  /// Sets this vessel point's vertical Dilution-of-Precision (VDOP)
  double getDopVertical() { return fdDopVertical; };

public:
  /// Returns this vessel's track recording rate, in seconds
  int getTrackRecordRate() { return iTrackRecordRate; };
  /// Returns this vessel's track recording status
  bool isTrackRecording() { return bTrackRecord; };

  // OTHER
public:

  // OTHER
public:
  /// Connects all children devices
  void connectDevice();
  /// Disconnects all children devices
  void disconnectDevice();
  /// Handled changes triggered by child devices
  void onDeviceDataFix();

public:
  /// Retrieves this object's content from the given QVCT source (file)
  void parseQVCT( const QDomElement& _rqDomElement );
  /// Stores this object's content to the given QVCT destination (file)
  void dumpQVCT( QXmlStreamWriter & _rqXmlStreamWriter ) const;

};

#endif // QVCT_CVESSELPOINT_HPP
