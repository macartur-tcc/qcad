// Auto generated by Testing Dashboard
// File        : scripts/Modify/BreakOut/Tests/BreakOutTest02.js
// Timestamp   : 2015-09-02 11:48:00
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function BreakOutTest02() {
    TdbTest.call(this, 'scripts/Modify/BreakOut/Tests/BreakOutTest02.js');
}

BreakOutTest02.prototype = new TdbTest();

BreakOutTest02.prototype.test00 = function() {
    qDebug('running BreakOutTest02.test00()...');
    this.setUp();
    this.importFile('scripts/Modify/BreakOut/Tests/data/polylines.dxf');
    TdbTest.clickOnWidget('MainWindow::CadQToolBar::CadToolBar::MainToolsPanel::ModifyToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadQToolBar::CadToolBar::ModifyToolsPanel::BreakOutButton');
    this.setToolOption('BreakOut/RemoveSegment', 'true');
    this.updateToolOptions();
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(15.503189, 65.010204);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(16.270408, 58.360969);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(16.014668, 50.433036);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(16.270408, 43.016582);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(16.781888, 35.855867);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(17.037628, 33.554209);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(15.758929, 21.278699);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(17.293367, 9.514668);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(3.910224438902743, new RVector(48.176, 36.5185, 0, true));
    var p = new RVector(16.781888, -5.57398);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(2.204719, -11.711735);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(-1.631378, -10.944515);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('BreakOutTest02_000.dxf');
    this.tearDown();
    qDebug('finished BreakOutTest02.test00()');
};

