<?

include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/BaseApi.php';
include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/service/ReasonsService.php';

class ReasonsController extends BaseApi
{
    protected $reasonsService;

    /**
     * ReasonsController constructor.
     * @param $request
     * @param $origin
     * @throws Exception
     */
    public function __construct($request) {
        parent::__construct($request,$this);
        $this->reasonsService = new ReasonsService();
    }

    /**
     * Example of an Endpoint
     */
     protected function GetDashboard() {
        if ($this->method == 'GET') {
            return $this->reasonsService->GetDashboard();
        } else {

        }
     }
}

?>