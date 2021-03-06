#--------------------------------------------------------------------
# Inviwo Core
ivw_project(inviwo-core)

#--------------------------------------------------------------------
# Add header files
set(HEADER_FILES
    ${IVW_INCLUDE_DIR}/inviwo/core/common/defaulttohighperformancegpu.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwo.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwoapplication.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwocore.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwocoredefine.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwomodule.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/inviwomodulefactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/moduleaction.h
    ${IVW_INCLUDE_DIR}/inviwo/core/common/modulecallback.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/buffer/buffer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/buffer/bufferram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/buffer/bufferramprecision.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/buffer/bufferrepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/camera.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/camerafactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/camerafactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/coordinatetransformer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/data.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/datagroup.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/datagrouprepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/datamapper.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/datarepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/diskrepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/basicmesh.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/edge.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/geometrytype.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/mesh.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/meshram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/meshrepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/plane.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/polygon.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/simplemesh.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/geometry/simplemeshcreator.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/histogram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/image.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/imageram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/imagerepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/imagetypes.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layerdisk.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layerram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layerramconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layerramprecision.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/image/layerrepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/light/baselightsource.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/light/diffuselight.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/light/directionallight.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/light/pointlight.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/light/spotlight.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/representationconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/representationconverterfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/representationconvertermetafactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/representationtraits.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/spatialdata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/transferfunction.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/transferfunctiondatapoint.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volume.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumeborder.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumedisk.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumeram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumeramconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumeramhistogram.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumeramprecision.h
    ${IVW_INCLUDE_DIR}/inviwo/core/datastructures/volume/volumerepresentation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/cameratrackball.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/event.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/eventhandler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/eventlistener.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/eventmatcher.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/eventpropagator.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/gestureevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/gesturestate.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/interactionevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/keyboardevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/keyboardkeys.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/mousebuttons.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/mouseevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/mouseinteractionevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/pickingevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/resizeevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/touchevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/touchstate.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/events/wheelevent.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/interactionhandler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/pickingaction.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/pickingcontroller.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/pickingmanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/pickingmapper.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/pickingstate.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/trackball.h
    ${IVW_INCLUDE_DIR}/inviwo/core/interaction/trackballobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/bytereaderutil.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datareader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datareaderdialog.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datareaderexception.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datareaderfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datawriter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datawriterfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datvolumereader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/datvolumewriter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/imagewriterutil.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/ivfvolumereader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/ivfvolumewriter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/rawvolumeramloader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/rawvolumereader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/deserializer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/nodedebugger.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serializable.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serialization.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serializationexception.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serializebase.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serializeconstants.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/serializer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/ticpp.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization/versionconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/tempfilehandle.h
    ${IVW_INCLUDE_DIR}/inviwo/core/io/textfilereader.h
    ${IVW_INCLUDE_DIR}/inviwo/core/links/linkconditions.h
    ${IVW_INCLUDE_DIR}/inviwo/core/links/linkevaluator.h
    ${IVW_INCLUDE_DIR}/inviwo/core/links/propertylink.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/containermetadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/metadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/metadatafactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/metadatamap.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/metadataowner.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/positionmetadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/processormetadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/processorwidgetmetadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata/propertyeditorwidgetmetadata.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/evaluationerrorhandler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/networklock.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/networkutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/portconnection.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/processornetwork.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/processornetworkconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/processornetworkevaluationobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/processornetworkevaluator.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/processornetworkobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/workspacemanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/network/workspaceutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/bufferport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/datainport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/dataoutport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/imageport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/inport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/inportiterable.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/meshport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/outport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/outportiterable.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/port.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portinspector.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portinspectorfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portinspectorfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/portinspectormanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/ports/volumeport.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/activityindicator.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/canvasprocessor.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/canvasprocessorwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processor.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorinfo.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorpair.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorstate.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processortags.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processortraits.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorwidgetfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorwidgetfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/processorwidgetobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/progressbar.h
    ${IVW_INCLUDE_DIR}/inviwo/core/processors/progressbarowner.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/advancedmaterialproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/boolcompositeproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/boolproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/buttonproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/cameraproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/compositeproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/compositepropertyobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/directoryproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/eventproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/filepatternproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/fileproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/imageeditorproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/invalidationlevel.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/minmaxproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/multifileproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/optionproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/ordinalproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/planeproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/positionproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/property.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyconverter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyconvertermanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyowner.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyownerobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertypresetmanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertysemantics.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertyvisibility.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertywidget.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertywidgetfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/propertywidgetfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/simplelightingproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/simpleraycastingproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/stipplingproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/stringproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/templateproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/transferfunctionproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/valuewrapper.h
    ${IVW_INCLUDE_DIR}/inviwo/core/properties/volumeindicatorproperty.h
    ${IVW_INCLUDE_DIR}/inviwo/core/rendering/meshdrawer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/rendering/meshdrawerfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/resources/resource.h
    ${IVW_INCLUDE_DIR}/inviwo/core/resources/resourcemanager.h
    ${IVW_INCLUDE_DIR}/inviwo/core/resources/resourcemanagerobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/resources/templateresource.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/assertion.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/buildinfo.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/callback.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/canvas.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/capabilities.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/clock.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/cloneableptr.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/colorbrewer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/colorconversion.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/commandlineparser.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/consolelogger.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/constexprhash.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/datetime.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/dialog.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/dialogfactory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/dialogfactoryobject.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/dispatcher.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/document.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/exception.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/factory.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/filedialog.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/filedialogstate.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/fileextension.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/filelogger.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/fileobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/filesystem.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/formatconversion.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/formatdispatching.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/formats.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/formatsdefinefunc.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/glm.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/imagecache.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/imageramutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/imagesampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/indexmapper.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/interpolation.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/intersection/rayplaneintersection.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/intersection/raysphereintersection.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/introspection.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/inviwosetupinfo.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/logcentral.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/logerrorcounter.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/memoryfilehandle.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/observer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/ostreamjoiner.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/pathtype.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/raiiutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/rendercontext.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/settings/linksettings.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/settings/settings.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/settings/systemsettings.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/shuntingyard.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/singlefileobserver.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/singleton.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/spatial4dsampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/spatialsampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/stacktrace.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/stdextensions.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/stringconversion.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/systemcapabilities.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/templatesampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/threadpool.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/timer.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/tinydirinterface.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/utilities.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/vectoroperations.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/volumeramutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/volumesampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/volumesequencesampler.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/volumesequenceutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/volumeutils.h
    ${IVW_INCLUDE_DIR}/inviwo/core/util/zip.h
)
ivw_group("Header Files" ${HEADER_FILES})

#--------------------------------------------------------------------
# Add source files
set(SOURCE_FILES
    common/inviwoapplication.cpp
    common/inviwocore.cpp
    common/inviwomodule.cpp
    common/inviwomodulefactoryobject.cpp
    common/moduleaction.cpp
    datastructures/buffer/buffer.cpp
    datastructures/buffer/bufferram.cpp
    datastructures/buffer/bufferrepresentation.cpp
    datastructures/camera.cpp
    datastructures/camerafactoryobject.cpp
    datastructures/datamapper.cpp
    datastructures/geometry/basicmesh.cpp
    datastructures/geometry/mesh.cpp
    datastructures/geometry/meshram.cpp
    datastructures/geometry/meshrepresentation.cpp
    datastructures/geometry/plane.cpp
    datastructures/geometry/simplemesh.cpp
    datastructures/geometry/simplemeshcreator.cpp
    datastructures/histogram.cpp
    datastructures/image/image.cpp
    datastructures/image/imageram.cpp
    datastructures/image/imagerepresentation.cpp
    datastructures/image/layer.cpp
    datastructures/image/layerdisk.cpp
    datastructures/image/layerram.cpp
    datastructures/image/layerramconverter.cpp
    datastructures/image/layerramprecision.cpp
    datastructures/image/layerrepresentation.cpp
    datastructures/light/baselightsource.cpp
    datastructures/representationconvertermetafactory.cpp
    datastructures/spatialdata.cpp
    datastructures/transferfunction.cpp
    datastructures/transferfunctiondatapoint.cpp
    datastructures/volume/volume.cpp
    datastructures/volume/volumeborder.cpp
    datastructures/volume/volumedisk.cpp
    datastructures/volume/volumeram.cpp
    datastructures/volume/volumeramconverter.cpp
    datastructures/volume/volumeramprecision.cpp
    datastructures/volume/volumerepresentation.cpp
    interaction/cameratrackball.cpp
    interaction/events/event.cpp
    interaction/events/eventhandler.cpp
    interaction/events/eventlistener.cpp
    interaction/events/eventmatcher.cpp
    interaction/events/gestureevent.cpp
    interaction/events/interactionevent.cpp
    interaction/events/keyboardevent.cpp
    interaction/events/mouseevent.cpp
    interaction/events/mouseinteractionevent.cpp
    interaction/events/pickingevent.cpp
    interaction/events/resizeevent.cpp
    interaction/events/touchevent.cpp
    interaction/events/wheelevent.cpp
    interaction/interactionhandler.cpp
    interaction/pickingaction.cpp
    interaction/pickingcontroller.cpp
    interaction/pickingmanager.cpp
    interaction/pickingmapper.cpp
    interaction/trackball.cpp
    io/bytereaderutil.cpp
    io/datareader.cpp
    io/datareaderdialog.cpp
    io/datareaderexception.cpp
    io/datareaderfactory.cpp
    io/datawriter.cpp
    io/datawriterfactory.cpp
    io/datvolumereader.cpp
    io/datvolumewriter.cpp
    io/imagewriterutil.cpp
    io/ivfvolumereader.cpp
    io/ivfvolumewriter.cpp
    io/rawvolumeramloader.cpp
    io/rawvolumereader.cpp
    io/serialization/deserializer.cpp
    io/serialization/nodedebugger.cpp
    io/serialization/serializationexception.cpp
    io/serialization/serializebase.cpp
    io/serialization/serializeconstants.cpp
    io/serialization/serializer.cpp
    io/serialization/versionconverter.cpp
    io/tempfilehandle.cpp
    io/textfilereader.cpp
    links/linkconditions.cpp
    links/linkevaluator.cpp
    links/propertylink.cpp
    metadata/metadata.cpp
    metadata/metadatamap.cpp
    metadata/metadataowner.cpp
    metadata/positionmetadata.cpp
    metadata/processormetadata.cpp
    metadata/processorwidgetmetadata.cpp
    metadata/propertyeditorwidgetmetadata.cpp
    network/evaluationerrorhandler.cpp
    network/networklock.cpp
    network/networkutils.cpp
    network/portconnection.cpp
    network/processornetwork.cpp
    network/processornetworkconverter.cpp
    network/processornetworkevaluationobserver.cpp
    network/processornetworkevaluator.cpp
    network/processornetworkobserver.cpp
    network/workspacemanager.cpp
    network/workspaceutils.cpp
    ports/imageport.cpp
    ports/inport.cpp
    ports/outport.cpp
    ports/port.cpp
    ports/portfactory.cpp
    ports/portfactoryobject.cpp
    ports/portinspector.cpp
    ports/portinspectorfactory.cpp
    ports/portinspectorfactoryobject.cpp
    ports/portinspectormanager.cpp
    processors/activityindicator.cpp
    processors/canvasprocessor.cpp
    processors/processor.cpp
    processors/processorfactory.cpp
    processors/processorinfo.cpp
    processors/processorpair.cpp
    processors/processortags.cpp
    processors/processorwidget.cpp
    processors/processorwidgetfactory.cpp
    processors/processorwidgetfactoryobject.cpp
    processors/processorwidgetobserver.cpp
    processors/progressbar.cpp
    properties/advancedmaterialproperty.cpp
    properties/boolcompositeproperty.cpp
    properties/boolproperty.cpp
    properties/buttonproperty.cpp
    properties/cameraproperty.cpp
    properties/compositeproperty.cpp
    properties/compositepropertyobserver.cpp
    properties/directoryproperty.cpp
    properties/eventproperty.cpp
    properties/filepatternproperty.cpp
    properties/fileproperty.cpp
    properties/imageeditorproperty.cpp
    properties/multifileproperty.cpp
    properties/optionproperty.cpp
    properties/planeproperty.cpp
    properties/positionproperty.cpp
    properties/property.cpp
    properties/propertyconverter.cpp
    properties/propertyconvertermanager.cpp
    properties/propertyfactory.cpp
    properties/propertyfactoryobject.cpp
    properties/propertyobserver.cpp
    properties/propertyowner.cpp
    properties/propertyownerobserver.cpp
    properties/propertypresetmanager.cpp
    properties/propertysemantics.cpp
    properties/propertywidget.cpp
    properties/propertywidgetfactory.cpp
    properties/propertywidgetfactoryobject.cpp
    properties/simplelightingproperty.cpp
    properties/simpleraycastingproperty.cpp
    properties/stipplingproperty.cpp
    properties/stringproperty.cpp
    properties/transferfunctionproperty.cpp
    properties/volumeindicatorproperty.cpp
    rendering/meshdrawerfactory.cpp
    resources/resourcemanager.cpp
    util/assertion.cpp
    util/canvas.cpp
    util/capabilities.cpp
    util/clock.cpp
    util/colorbrewer.cpp
    util/colorconversion.cpp
    util/commandlineparser.cpp
    util/consolelogger.cpp
    util/dialogfactory.cpp
    util/dialogfactoryobject.cpp
    util/document.cpp
    util/exception.cpp
    util/filedialog.cpp
    util/fileextension.cpp
    util/filelogger.cpp
    util/fileobserver.cpp
    util/filesystem.cpp
    util/formatconversion.cpp
    util/formatdispatching.cpp
    util/formats.cpp
    util/imagecache.cpp
    util/imageramutils.cpp
    util/imagesampler.cpp
    util/inviwosetupinfo.cpp
    util/logcentral.cpp
    util/logerrorcounter.cpp
    util/memoryfilehandle.cpp
    util/observer.cpp
    util/rendercontext.cpp
    util/settings/linksettings.cpp
    util/settings/settings.cpp
    util/settings/systemsettings.cpp
    util/shuntingyard.cpp
    util/singlefileobserver.cpp
    util/spatial4dsampler.cpp
    util/stacktrace.cpp
    util/stringconversion.cpp
    util/systemcapabilities.cpp
    util/threadpool.cpp
    util/timer.cpp
    util/tinydirinterface.cpp
    util/utilities.cpp
    util/volumesampler.cpp
    util/volumesequencesampler.cpp
    util/volumesequenceutils.cpp
    util/volumeutils.cpp
)

#--------------------------------------------------------------------
# include implementation for build info - the build info will be 
# updated during every compilation
if(IVW_EMBED_BUILDINFO)
    list(APPEND SOURCE_FILES "${CMAKE_BINARY_DIR}/modules/_generated/inviwo_buildinfo.cpp")
else()
    list(APPEND SOURCE_FILES util/buildinfoini.cpp)
endif()

ivw_group("Source Files" ${SOURCE_FILES})

#--------------------------------------------------------------------
# Optimize compilation with pre-compilied headers
set(PCH_PATH_FILES
    ${IVW_INCLUDE_DIR}/inviwo/core/common
    ${IVW_INCLUDE_DIR}/inviwo/core/io/serialization
    ${IVW_INCLUDE_DIR}/inviwo/core/metadata
    ${IVW_INCLUDE_DIR}/inviwo/core/ports
    ${IVW_INCLUDE_DIR}/inviwo/core/util
    ${IVW_INCLUDE_DIR}/inviwo/core/util/settings
)
ivw_add_pch_path(${PCH_PATH_FILES})

set(TEST_FILES
    tests/unittests/inviwo-core-unittest-main.cpp
    tests/unittests/commandlineparser-test.cpp
    tests/unittests/dataformats-test.cpp
    tests/unittests/dispatch-test.cpp
    tests/unittests/picking-test.cpp
    tests/unittests/metadata-test.cpp
    tests/unittests/serialize-container-test.cpp
    tests/unittests/serializer-test.cpp
    tests/unittests/filesystem-test.cpp
    tests/unittests/volumesequenceutils-tests.cpp
    tests/unittests/conversion-test.cpp
    tests/unittests/document-test.cpp
    tests/unittests/utilities-test.cpp
    tests/unittests/glm-test.cpp
    tests/unittests/zip-test.cpp
)
ivw_add_unittest(${TEST_FILES})


# Special Core Defines
remove_definitions(-DHAVE_CONFIG_H)
# Define Build Type if not empty
if(NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
    add_definitions(-DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")
endif()
add_definitions(-DCMAKE_GENERATOR="${CMAKE_GENERATOR}")

#--------------------------------------------------------------------
# Create library
add_library(inviwo-core ${SOURCE_FILES} ${HEADER_FILES})

#--------------------------------------------------------------------
# Define standard defintions
ivw_define_standard_definitions(IVW_CORE inviwo-core)
ivw_define_standard_properties(inviwo-core)

#--------------------------------------------------------------------
# Add core folders to includes
ivw_include_directories(${IVW_INCLUDE_DIR})
ivw_include_directories(${IVW_EXTENSIONS_DIR})
ivw_include_directories(${IVW_ROOT_DIR})
ivw_include_directories(${IVW_MODULE_DIR})
# Add path for external modules
if (NOT "${IVW_EXTERNAL_MODULES}" STREQUAL "")
    foreach(dir ${IVW_EXTERNAL_MODULES})
        ivw_include_directories(${dir})
        get_filename_component(dir_parent ${dir} PATH)
        ivw_include_directories(${dir_parent})
    endforeach()
endif()
ivw_include_directories(${CMAKE_BINARY_DIR}/modules/_generated)

# Add core dependencies to this list
ivw_add_dependencies(TiCPP)

if(IVW_SIGAR)
    ivw_add_dependencies(Sigar)
endif()
if(WIN32)
    ivw_add_dependencies(stackwalker)
endif()
if(APPLE)
   find_library(CORESERVICES_LIBRARY CoreServices)
   mark_as_advanced(CORESERVICES_LIBRARY)
   target_link_libraries(inviwo-core ${CORESERVICES_LIBRARY})
endif (APPLE)

#Optimize compiliation with PCH etc
ivw_compile_optimize()

#--------------------------------------------------------------------
# Make package (for other projects to find)
ivw_set_cpack_name(core)
ivw_make_package(InviwoCore inviwo-core)

if(IVW_UNITTESTS)
    ivw_make_unittest_target(core inviwo-core)
endif()


#--------------------------------------------------------------------
# Generate build info - the build info will be updated during every compilation

# make a clean help script
set(build_info_script_list
    "include(${IVW_ROOT_DIR}/cmake/globalutils.cmake)"
    "ivw_generate_build_info(${IVW_CMAKE_TEMPLATES}/inviwo_buildinfo_template.cpp"
    "    ${IVW_CMAKE_TEMPLATES}/inviwo_buildinfo_template.ini"
    "    ${CMAKE_BINARY_DIR}/modules/_generated/inviwo_buildinfo.cpp"
    "    inviwo_buildinfo.ini"
    "    ${IVW_MODULE_DIR} ${IVW_EXTERNAL_MODULES})"
)
string(REPLACE ";" "\n" build_info_script "${build_info_script_list}")
file(WRITE "${IVW_CMAKE_BINARY_MODULE_DIR}/build_info.cmake" ${build_info_script})

# Custom target for updating the build information (this target is always out-of-date)
add_custom_target(inviwo-buildinfo-header ALL
    BYPRODUCTS "${CMAKE_BINARY_DIR}/modules/_generated/inviwo_buildinfo.cpp"
    COMMAND ${CMAKE_COMMAND} -DINI_DEST_PATH="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/" -P "${IVW_CMAKE_BINARY_MODULE_DIR}/build_info.cmake"
    WORKING_DIRECTORY ${OUTPUT_DIR}
    COMMENT "Generating inviwo build info (buildinfo)"
    VERBATIM
)

option(IVW_EMBED_BUILDINFO "Embed buildinfo into the binary file instead of using a ini file, will force inviwo-core to recompile every build" OFF)
if(IVW_EMBED_BUILDINFO)
    add_dependencies("inviwo-core" "inviwo-buildinfo-header")
    target_compile_definitions("inviwo-core" PRIVATE "IVW_EMBED_BUILDINFO")
else()
    ## ensure that the ini file containing the build info is packaged and installed to the bin folder
    install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/inviwo_buildinfo.ini DESTINATION bin COMPONENT modules CONFIGURATIONS Release Debug)
endif()
#--------------------------------------------------------------------
