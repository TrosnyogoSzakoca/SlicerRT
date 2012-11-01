/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care

==============================================================================*/

// MRMLDoseAccumulation includes
#include "vtkMRMLContourComparisonNode.h"

// MRML includes
#include <vtkMRMLScene.h>
#include <vtkMRMLVolumeNode.h>

// VTK includes
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

// STD includes
#include <sstream>

//------------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLContourComparisonNode);

//----------------------------------------------------------------------------
vtkMRMLContourComparisonNode::vtkMRMLContourComparisonNode()
{
  this->ReferenceContourNodeId = NULL;
  this->CompareContourNodeId = NULL;
  this->RasterizationReferenceVolumeNodeId = NULL;

  this->DiceCoefficient = -1.0;
  this->TruePositivesPercent = -1.0;
  this->TrueNegativesPercent = -1.0;
  this->FalsePositivesPercent = -1.0;
  this->FalseNegativesPercent = -1.0;
  this->ReferenceCenter[0] = this->ReferenceCenter[1] = this->ReferenceCenter[2] = 0.0;
  this->CompareCenter[0] = this->CompareCenter[1] = this->CompareCenter[2] = 0.0;
  this->ReferenceVolumeCc = -1.0;
  this->CompareVolumeCc = -1.0;
  this->ResultsValidOff();

  this->HideFromEditors = false;
}

//----------------------------------------------------------------------------
vtkMRMLContourComparisonNode::~vtkMRMLContourComparisonNode()
{
  this->SetReferenceContourNodeId(NULL);
  this->SetCompareContourNodeId(NULL);
  this->SetRasterizationReferenceVolumeNodeId(NULL);
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  // Write all MRML node attributes into output stream
  vtkIndent indent(nIndent);

  if ( this->ReferenceContourNodeId )
    {
    of << indent << " ReferenceContourNodeId=\"" << this->ReferenceContourNodeId << "\"";
    }
  if ( this->CompareContourNodeId )
    {
    of << indent << " CompareContourNodeId=\"" << this->CompareContourNodeId << "\"";
    }
  if ( this->RasterizationReferenceVolumeNodeId )
    {
    of << indent << " ReferenceVolumeNodeId=\"" << this->RasterizationReferenceVolumeNodeId << "\"";
    }

  of << indent << " DiceCoefficient=\"" << this->DiceCoefficient << "\"";
  of << indent << " TruePositivesPercent=\"" << this->TruePositivesPercent << "\"";
  of << indent << " TrueNegativesPercent=\"" << this->TrueNegativesPercent << "\"";
  of << indent << " FalsePositivesPercent=\"" << this->FalsePositivesPercent << "\"";
  of << indent << " FalseNegativesPercent=\"" << this->FalseNegativesPercent << "\"";

  {
    std::stringstream ss;
    of << indent << " ReferenceCenter=\"";
    for (int i=0; i<3; ++i)
    {
      ss << this->ReferenceCenter;
      of << ss.str() << "|";
    }
    of << "\"";
  }
  {
    std::stringstream ss;
    of << indent << " CompareCenter=\"";
    for (int i=0; i<3; ++i)
    {
      ss << this->CompareCenter;
      of << ss.str() << "|";
    }
    of << "\"";
  }

  of << indent << " ReferenceVolumeCc=\"" << this->ReferenceVolumeCc << "\"";
  of << indent << " CompareVolumeCc=\"" << this->CompareVolumeCc << "\"";

  of << indent << " ResultsValid=\"" << (this->ResultsValid ? "true" : "false") << "\"";
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::ReadXMLAttributes(const char** atts)
{
  vtkMRMLNode::ReadXMLAttributes(atts);

  // Read all MRML node attributes from two arrays of names and values
  const char* attName;
  const char* attValue;

  while (*atts != NULL) 
    {
    attName = *(atts++);
    attValue = *(atts++);

    if (!strcmp(attName, "ReferenceContourNodeId")) 
      {
      std::stringstream ss;
      ss << attValue;
      this->SetAndObserveReferenceContourNodeId(ss.str().c_str());
      }
    else if (!strcmp(attName, "CompareContourNodeId")) 
      {
      std::stringstream ss;
      ss << attValue;
      this->SetAndObserveCompareContourNodeId(ss.str().c_str());
      }
    else if (!strcmp(attName, "ReferenceVolumeNodeId")) 
      {
      std::stringstream ss;
      ss << attValue;
      this->SetAndObserveReferenceVolumeNodeId(ss.str().c_str());
      }
    else if (!strcmp(attName, "DiceCoefficient")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->DiceCoefficient = doubleAttValue;
      }
    else if (!strcmp(attName, "TruePositivesPercent")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->TruePositivesPercent = doubleAttValue;
      }
    else if (!strcmp(attName, "TrueNegativesPercent")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->TrueNegativesPercent = doubleAttValue;
      }
    else if (!strcmp(attName, "FalsePositivesPercent")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->FalsePositivesPercent = doubleAttValue;
      }
    else if (!strcmp(attName, "FalseNegativesPercent")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->FalseNegativesPercent = doubleAttValue;
      }
    else if (!strcmp(attName, "ReferenceCenter")) 
      {
      std::stringstream ss;
      ss << attValue;
      std::string valueStr = ss.str();
      std::string separatorCharacter("|");

      size_t separatorPosition = valueStr.find( separatorCharacter );

        {
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->ReferenceCenter[0] = doubleValue;
        }
        {
        valueStr = valueStr.substr( separatorPosition+1 );
        separatorPosition = valueStr.find( separatorCharacter );
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->ReferenceCenter[1] = doubleValue;
        }
        {
        valueStr = valueStr.substr( separatorPosition+1 );
        separatorPosition = valueStr.find( separatorCharacter );
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->ReferenceCenter[2] = doubleValue;
        }
      }
    else if (!strcmp(attName, "CompareCenter")) 
      {
      std::stringstream ss;
      ss << attValue;
      std::string valueStr = ss.str();
      std::string separatorCharacter("|");

      size_t separatorPosition = valueStr.find( separatorCharacter );

        {
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->CompareCenter[0] = doubleValue;
        }
        {
        valueStr = valueStr.substr( separatorPosition+1 );
        separatorPosition = valueStr.find( separatorCharacter );
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->CompareCenter[1] = doubleValue;
        }
        {
        valueStr = valueStr.substr( separatorPosition+1 );
        separatorPosition = valueStr.find( separatorCharacter );
        std::stringstream ss;
        ss << valueStr.substr(0, separatorPosition);
        double doubleValue;
        ss >> doubleValue;
        this->CompareCenter[2] = doubleValue;
        }
      }
    else if (!strcmp(attName, "ReferenceVolumeCc")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->ReferenceVolumeCc = doubleAttValue;
      }
    else if (!strcmp(attName, "CompareVolumeCc")) 
      {
      std::stringstream ss;
      ss << attValue;
      double doubleAttValue;
      ss >> doubleAttValue;
      this->CompareVolumeCc = doubleAttValue;
      }
    else if (!strcmp(attName, "ResultsValid")) 
      {
      this->ResultsValid = (strcmp(attValue,"true") ? false : true);
      }
    }
}

//----------------------------------------------------------------------------
// Copy the node's attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, VolumeID
void vtkMRMLContourComparisonNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  this->DisableModifiedEventOn();

  vtkMRMLContourComparisonNode *node = (vtkMRMLContourComparisonNode *) anode;

  this->SetAndObserveReferenceContourNodeId(node->ReferenceContourNodeId);
  this->SetAndObserveCompareContourNodeId(node->CompareContourNodeId);
  this->SetAndObserveReferenceVolumeNodeId(node->RasterizationReferenceVolumeNodeId);

  this->DiceCoefficient = node->DiceCoefficient;
  this->TruePositivesPercent = node->TruePositivesPercent;
  this->TrueNegativesPercent = node->TrueNegativesPercent;
  this->FalsePositivesPercent = node->FalsePositivesPercent;
  this->FalseNegativesPercent = node->FalseNegativesPercent;
  this->SetReferenceCenter( node->GetReferenceCenter() );
  this->SetCompareCenter( node->GetCompareCenter() );
  this->ReferenceVolumeCc = node->ReferenceVolumeCc;
  this->CompareVolumeCc = node->CompareVolumeCc;
  this->ResultsValid = node->ResultsValid;

  this->DisableModifiedEventOff();
  this->InvokePendingModifiedEvent();
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkMRMLNode::PrintSelf(os,indent);

  os << indent << "ReferenceContourNodeId:   " << this->ReferenceContourNodeId << "\n";
  os << indent << "CompareContourNodeId:   " << this->CompareContourNodeId << "\n";
  os << indent << "ReferenceVolumeNodeId:   " << this->RasterizationReferenceVolumeNodeId << "\n";

  os << indent << " DiceCoefficient=\"" << this->DiceCoefficient << "\"";
  os << indent << " TruePositivesPercent=\"" << this->TruePositivesPercent << "\"";
  os << indent << " TrueNegativesPercent=\"" << this->TrueNegativesPercent << "\"";
  os << indent << " FalsePositivesPercent=\"" << this->FalsePositivesPercent << "\"";
  os << indent << " FalseNegativesPercent=\"" << this->FalseNegativesPercent << "\"";

  {
    std::stringstream ss;
    os << indent << " ReferenceCenter=\"";
    for (int i=0; i<3; ++i)
    {
      ss << this->ReferenceCenter;
      os << ss.str() << "|";
    }
    os << "\"";
  }
  {
    std::stringstream ss;
    os << indent << " CompareCenter=\"";
    for (int i=0; i<3; ++i)
    {
      ss << this->CompareCenter;
      os << ss.str() << "|";
    }
    os << "\"";
  }

  os << indent << " ReferenceVolumeCc=\"" << this->ReferenceVolumeCc << "\"";
  os << indent << " CompareVolumeCc=\"" << this->CompareVolumeCc << "\"";

  os << indent << " ResultsValid=\"" << (this->ResultsValid ? "true" : "false") << "\"";}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::SetAndObserveReferenceContourNodeId(const char* id)
{
  if (this->ReferenceContourNodeId)
  {
    this->Scene->RemoveReferencedNodeID(this->ReferenceContourNodeId, this);
  }

  this->SetReferenceContourNodeId(id);

  if (id)
  {
    this->Scene->AddReferencedNodeID(this->ReferenceContourNodeId, this);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::SetAndObserveCompareContourNodeId(const char* id)
{
  if (this->CompareContourNodeId)
  {
    this->Scene->RemoveReferencedNodeID(this->CompareContourNodeId, this);
  }

  this->SetCompareContourNodeId(id);

  if (id)
  {
    this->Scene->AddReferencedNodeID(this->CompareContourNodeId, this);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::SetAndObserveReferenceVolumeNodeId(const char* id)
{
  if (this->RasterizationReferenceVolumeNodeId)
  {
    this->Scene->RemoveReferencedNodeID(this->RasterizationReferenceVolumeNodeId, this);
  }

  this->SetRasterizationReferenceVolumeNodeId(id);

  if (id)
  {
    this->Scene->AddReferencedNodeID(this->RasterizationReferenceVolumeNodeId, this);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLContourComparisonNode::UpdateReferenceID(const char *oldID, const char *newID)
{
  if (this->ReferenceContourNodeId && !strcmp(oldID, this->ReferenceContourNodeId))
    {
    this->SetAndObserveReferenceContourNodeId(newID);
    }
  if (this->CompareContourNodeId && !strcmp(oldID, this->CompareContourNodeId))
    {
    this->SetAndObserveCompareContourNodeId(newID);
    }
  if (this->RasterizationReferenceVolumeNodeId && !strcmp(oldID, this->RasterizationReferenceVolumeNodeId))
    {
    this->SetAndObserveReferenceVolumeNodeId(newID);
    }
}