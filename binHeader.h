class BinaryFileHeader
{
 public:
  uint32_t magicNumber;         /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};
