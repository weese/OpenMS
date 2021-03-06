// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2014.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Clemens Groepl, Andreas Bertsch $
// $Authors: Chris Bauer $
// --------------------------------------------------------------------------


#ifndef OPENMS_FORMAT_FASTAITERATOR_H
#define OPENMS_FORMAT_FASTAITERATOR_H

#include <OpenMS/CHEMISTRY/PepIterator.h>
#include <OpenMS/CONCEPT/Exception.h>
#include <fstream>
#include <vector>

namespace OpenMS
{

/**
@brief Iterator over FASTA file

Iterates over FASTA file without loading it into memory. It holds just one entry in memory.
@see FastaIteratorIntern.h
*/
  class OPENMS_DLLAPI FastaIterator :
    public PepIterator
  {

public:

    typedef std::pair<String, String> FASTAEntry;
    /**
    @brief constructor
    */
    FastaIterator();


    /**
    @brief destructor
    */
    virtual ~FastaIterator();

    /**
    @brief * operator for getting the iterator's value
    @return FASTAEntry
    @throw InvalidIterator if iterator was not initialized
    */
    virtual FASTAEntry operator*();

    /**
    @brief pre-increment Operator for the iterator
    @return reference to PepIterator
    @throw Exception::InvalidIterator if iterator was not initialized
    */
    virtual PepIterator & operator++();

    /**
    @brief post-increment Operator for the iterator
    @return pointer to PepIterator
    @throw Exception::InvalidIterator if iterator was not initialized
    */
    virtual PepIterator * operator++(int i);

    /**
    @brief setter for FASTAfile
    @param f Name of the fasta file
    @throw Exception::FileNotFound
    @throw ParseError is thrown if the file could not be parsed
    */
    virtual void setFastaFile(const String & f);

    /**
    @brief getter for FASTA file
    @return String with file location
    */
    virtual String getFastaFile();

    /**
    @brief setter for spectrum
    @note note available for FastaIterator
    @throw Exception::NotImplemented
    */
    virtual void setSpectrum(const std::vector<double> &)
    {
      throw Exception::NotImplemented(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }

    /**
    @brief getter for spectrum
    @note note available for FastaIterator
    @throw Exception::NotImplemented
    */
    virtual const std::vector<double> & getSpectrum()
    {
      throw Exception::NotImplemented(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }

    /**
    @brief setter for tolerance
    @note note available for FastaIterator
    @throw Exception::NotImplemented
    */
    virtual void setTolerance(double /* t */)
    {
      throw Exception::NotImplemented(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }

    /**
    @brief getter for tolerance
    @note note available for FastaIterator
    @return tolerance
    @throw Exception::NotImplemented
    */
    virtual double getTolerance()
    {
      throw Exception::NotImplemented(__FILE__, __LINE__, __PRETTY_FUNCTION__);
    }

    /**
    @brief initializing of iterator
    @return true if everything went right
    @throw Exception::InvalidIterator if fastaFile was not set
    */
    virtual bool begin();

    /**
    @brief indicates whether iterator is at end
    @return bool true if iterator is at end
    */
    virtual bool isAtEnd();

    /**
    @brief needed by Factory
    @return const string name of class
    */
    static const String getProductName()
    {
      return "FastaIterator";
    }

    /**
    @brief needed by Factory
    @return pointer to new object
    */
    static PepIterator * create()
    {
      return new FastaIterator;
    }

protected:
    /**
    @brief gets the next string
    @return string
    */
    virtual std::string next_();

    bool is_at_end_;     ///< bool indicated whether iterator is at end

    std::ifstream input_file_;     ///< input file

    String fasta_file_;     ///< fasta file location

    std::string actual_seq_;     ///< actual sequence

    std::string header_;     ///< actual fasta header

    std::string last_header_;     ///< last fasta header

private:
    /**
      @brief copy constructor
      */
    FastaIterator(const FastaIterator &);

    /**
      @brief Assignment
      */
    FastaIterator & operator=(const FastaIterator &);


  };
}
#endif // OPENMS_FORMAT_FASTAITERATOR_H
