<?

abstract class Entity
{
    /**
     * @Column(type="integer")
     * @var int
     **/
    public $CreatedByUserId = 143;

    /**
     * @Column(type="datetime")
     * @var int
     **/
    public $CreatedDate;
    /**
     * @Column(type="integer")
     * @var int
     **/
    public $ModifiedByUserId;

    /**
     * @Column(type="datetime")
     * @var int
     **/
    public $ModifiedDate;

    /**
     * @Column(type="boolean")
     * @var int
     **/
    public $Active = true;

    public function setCreatedByUserId($CreatedByUserId)
    {
        $this->CreatedByUserId = $CreatedByUserId;
    }

    public function getCreatedByUserId()
    {
        return $this->CreatedByUserId;
    }

    public function setCreatedDate($CreatedDate)
    {
        $this->CreatedDate = $CreatedDate;
    }

    public function getCreatedDate()
    {
        return $this->CreatedDate;
    }

    public function setModifiedByUserId($ModifiedByUserId)
    {
        $this->ModifiedByUserId = $ModifiedByUserId;
    }

    public function getModifiedByUserId()
    {
        return $this->ModifiedByUserId;
    }

    public function setModifiedDate($ModifiedDate)
    {
        $this->ModifiedDate = $ModifiedDate;
    }

    public function getModifiedDate()
    {
        return $this->ModifiedDate;
    }

    public function setActive($Active)
    {
        $this->Active = $Active;
    }

    public function getActive()
    {
        return $this->Active;
    }



}

?>